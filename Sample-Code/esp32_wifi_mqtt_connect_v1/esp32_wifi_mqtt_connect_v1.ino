/**
 * ESP32 Wi-Fi & MQTT Connection v1
 *
 * Demo of connecting to a Wi-Fi Network.
 * Demo of connecting to MQTT after successfully connecting to Wi-Fi
 *
 * Filename:        esp32_wifi_mqtt_connect_v1.ino
 *
 * Assessment Name: n/a
 * Due:             n/a
 * Name:            Adrian Gould
 *
 * Note:
 * - require the Adafruit MQTT Library
 * - install with dependencies
 */


/**--------------------------------------------------------------------------
 * External Source, Package, Module includes
 *---------------------------------------------------------------------------*/
// Includes
#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>


/**--------------------------------------------------------------------------
 * Declarations 
 *---------------------------------------------------------------------------*/

// Debugging Macros
//   1 = Debugging on
//   0 = Debugging off
#define DEBUG 1

#if DEBUG
  #define DEBUG_PRINT(data) Serial.print(data); Serial.print(" ");
  #define DEBUG_PRINTLN(data) Serial.println(data)
  #define DEBUG_BEGIN(speed) Serial.begin(speed); while(!Serial) {}
#else
  #define DEBUG_PRINT(debug)
  #define DEBUG_PRINTLN(debug)
  #define DEBUG_BEGIN(speed)
#endif

// Macros
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
// #define MQTT_BROKER "BROKER_HOST_NAME_OR_IP_ADDRESS"
#define MQTT_BROKER   "10.25.35.135"
#define MQTT_PORT     1883

#define MAX_ATTEMPTS 5
#define RETRY_PERIOD 1000
#define RETRY_BACKOFF 500

// Constants

const char* WIFI_SSID = "NMT-IoT";
const char* WIFI_PASS = "Its!Working";

// Variables
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_BROKER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD);


/**--------------------------------------------------------------------------
 * Hardware/Software Configuration
 *---------------------------------------------------------------------------*/
// Setting Up Hardware

void setup()
{
/**
 * This code executes ONCE per Power-up or Wake 
 */
  DEBUG_BEGIN(9600);  // Higher serial port speed 115200
  delay(2000);        // Allow the Serial port to connect
  int connected_wifi = initWiFi();         // Call the Connect to Wi-Fi function
  
  DEBUG_PRINTLN("");

  if (!connected_wifi) {
    DEBUG_PRINT("No Wi-fi Connection");
  } else {

    wifiDetails();
  
    int connected_mqtt = initMQTT();
    if (!connected_mqtt) {
      DEBUG_PRINTLN("MQTT Connection Failed");
    } else {
      DEBUG_PRINTLN("MQTT Connection Successful");
    }

    DEBUG_PRINTLN("Set-up complete");
  }
  DEBUG_PRINTLN();

}

/**--------------------------------------------------------------------------
 * Master/Main Loop
 *---------------------------------------------------------------------------*/
void loop()
{
  /**
   * This code executes for as long as the hardware
   * is turned on, or not asleep
   */

  
}

/**--------------------------------------------------------------------------
 * Functions & Helper Code
 *---------------------------------------------------------------------------*/
void wifiDetails(){
  DEBUG_PRINT("Hostname:");
  DEBUG_PRINTLN(WiFi.getHostname());

  DEBUG_PRINT("SSID:");
  DEBUG_PRINTLN(WIFI_SSID);

  DEBUG_PRINT("Signal Strength:");
  DEBUG_PRINTLN(WiFi.RSSI());

  DEBUG_PRINT("Ip Address:");
  DEBUG_PRINTLN(WiFi.localIP());
}

bool initWiFi() {
  int attempts = 0; // current attempt count

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(10);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  DEBUG_PRINT("Connecting to Wi-Fi ");
  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPTS) {
    DEBUG_PRINT(".");
    delay(RETRY_PERIOD + RETRY_BACKOFF * attempts);
    attempts++;
  }

  return attempts < MAX_ATTEMPTS;
}

bool initMQTT()
{
  int attempts = 0;
  int8_t mqttConnectionResult;

  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("Connecting to MQTT Broker/Server: ");

  while ((mqttConnectionResult = mqtt.connect()) !=0 && attempts < MAX_ATTEMPTS)
  {
    DEBUG_PRINT(".");
    delay(RETRY_PERIOD + RETRY_BACKOFF * attempts);
    attempts++;

    if(mqttConnectionResult !=0) {
      mqtt.disconnect();
    }
  }
  return attempts < MAX_ATTEMPTS;
}
