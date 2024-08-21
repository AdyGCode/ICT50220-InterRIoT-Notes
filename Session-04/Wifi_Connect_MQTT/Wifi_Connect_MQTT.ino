/**
 * ESP32 WiFi & MQTT
 * 
 * Project: WiFi_Connect_MQTT
 *
 * Requires:
 *   - Adafruit MQTT
 *   - Adafruit MQTT Client
 *   - Adafruit account (https://adafruit.com)
 */

#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define IO_USERNAME "ADAFRUIT_USERNAME"
#define IO_KEY "ADAFRUIT_KEY"
#define IO_SERVER "ADAFRUIT_SERVER_URI"
#define IO_SERVERPORT ADAFRUIT_IO_PORT_NUMBER

#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 250
#define MAX_ATTEMPTS 5

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_SERVERPORT, IO_USERNAME, IO_KEY);

void setup() {
  Serial.begin(9600);

  bool wifiConnected = wiFiConnect();
  if (wifiConnected) {
    Serial.println("Wi-Fi Connected");
    wiFiDetails();

    bool mqttConnected = mqttConnect();
    if (mqttConnected) {
      Serial.println("MQTT Connected");
    } else {
      Serial.println("MQTT Connection Failed.");
    }

  } else {
    Serial.println("Wi-Fi Connection Failed");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

bool wiFiConnect() {
  uint8_t attempts = 0;  // Unsigned 8 bit integer

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPTS) {
    Serial.print(".");
    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);
    attempts++;
  }

  return attempts < MAX_ATTEMPTS;
}

bool mqttConnect() {
  uint8_t attempts = 0;         // Unsigned 8 bit integer
  int8_t mqttConnectionResult;  // signed 8 bit integer

  Serial.println("Connecting to MQTT...");

  while ((mqttConnectionResult = mqtt.connect()) != 0 && attempts < MAX_ATTEMPTS) {
    Serial.print(".");
    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);
    attempts++;

    if (mqttConnectionResult != 0) {
      mqtt.disconnect();
    }
  }

  return attempts < MAX_ATTEMPTS;
}


void wiFiDetails() {
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