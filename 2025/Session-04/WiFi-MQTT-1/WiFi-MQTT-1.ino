/**
 * ESP32 WiFi & MQTT Connection v1
 * 
 * Sketch Name: WiFi-MQTT-1.ino
 * Author:      Adrian Gould
 * 
 * Description: This sketch attempts to:
 *  - create a connection to a given WiFi SSID
 *  - if the WiFi is connected then
 *    attempts to connect to a given MQTT Broker/Server.
 *
 * Use the Library Manager to install:
 *  - Adafruit MQTT Library
 *
 * See also: 
 * https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
 *
 *
 * --------------------------------------------------------------------
 * Sample output from ESP32 in Debug Mode
 * 
 * ets Jul 29 2019 12:21:46
 * 
 * rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
 * configsip: 0, SPIWP:0xee
 * clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
 * mode:DIO, clock div:1
 * load:0x3fff0030,len:4916
 * load:0x40078000,len:16436
 * load:0x40080400,len:4
 * ho 8 tail 4 room 4
 * load:0x40080404,len:3524
 * entry 0x400805b8
 * Connecting to WiFi...
 * .
 * WiFi Connected.
 *
 * Local IP:        10.25.35.152
 * Gateway IP:      10.25.35.1
 * Signal Strength: -52
 * Hostname:        esp32-65465C
 * 
 * Connecting to MQTT Broker/Server...
 * ...
 * MQTT Connected.
 */

/**
 * Include the required Libraries for MQTT and WiFi 
 */
#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

/**
 * Define Macros for constant values
 *
 * - MQTT Connection details
 * - Retry values
 * - Component Pins
 */
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_SERVER "SERVER_HOST_NAME_OR_IP_ADDRESS"
#define MQTT_SERVERPORT 1883

#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 500
#define MAX_ATTEMPTS 5

#define LED_RED_1 25
#define LED_GREEN_1 26
#define LED_BLUE_1 27

/* Set to FALSE if you do not want the Serial port output */
#define DEBUG true

/**
 * Define the WiFi SSID and Password
 */
const char* ssid = "SSID_HERE";
const char* password = "SSID_SPECIFIC_PASSWORD_HERE";

/**
 * Create the WiFi Client and MQTT Client for connections
 */
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_PASSWORD);


/**
 * The setup code is executed EVERY time the ESP32 restarts.
 * This includes on:
 *   - Inital power up
 *   - Hard reset of device
 *   - On wake from sleep
 */
void setup() {

  /**
   * Serial port connection is being used as a method of DEBUGging only.
   */
  if (DEBUG) {
    Serial.begin(115200);
  }

  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(LED_BLUE_1, OUTPUT);

  digitalWrite(LED_RED_1, HIGH);
  digitalWrite(LED_GREEN_1, LOW);
  digitalWrite(LED_BLUE_1, LOW);

  bool wiFiConnected = wiFiConnect();

  if (wiFiConnected) {
    if (DEBUG) {
      Serial.println("WiFi Connected.");
    }

    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_GREEN_1, HIGH);
    digitalWrite(LED_BLUE_1, LOW);
    wiFiDetails();

    bool mqttConnected = mqttConnect();

    if (mqttConnected) {
      if (DEBUG) {
        Serial.println("MQTT Connected.");
      }

      digitalWrite(LED_BLUE_1, HIGH);
      delay(RETRY_PERIOD);
      digitalWrite(LED_BLUE_1, LOW);
    } else {
      if (DEBUG) {
        Serial.println("MQTT Connection Failed.");
      }

      digitalWrite(LED_RED_1, HIGH);
      digitalWrite(LED_GREEN_1, LOW);
      digitalWrite(LED_BLUE_1, LOW);
    }

  } else {
    if (DEBUG) {
      Serial.println("WiFi Connection Failed.");
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

bool wiFiConnect() {
  int attempts = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  if (DEBUG) {
    Serial.println("Connecting to WiFi...");
  }

  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPTS) {

    if (DEBUG) {
      Serial.print(".");
    }

    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);
    attempts++;
  }

  return attempts < MAX_ATTEMPTS;
}

bool mqttConnect() {

  uint8_t attempts = 0;
  int8_t mqttConnectionResult;

  if (DEBUG) {
    Serial.println();
    Serial.println("Connecting to MQTT Broker/Server...");
  }

  while ((mqttConnectionResult = mqtt.connect()) != 0 && attempts < MAX_ATTEMPTS) {

    if (DEBUG) {
      Serial.print(".");
    }

    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);
    attempts++;

    if (mqttConnectionResult != 0) {
      mqtt.disconnect();
    }
  }

  return attempts < MAX_ATTEMPTS;
}



void wiFiDetails() {
  if (DEBUG) {
    Serial.println();
    Serial.print("Local IP:        ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway IP:      ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Signal Strength: ");
    Serial.println(WiFi.RSSI());
    Serial.print("Hostname:        ");
    Serial.println(WiFi.getHostname());
  }
}