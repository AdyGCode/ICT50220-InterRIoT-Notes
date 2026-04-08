/**
 * ESP32 Wi-Fi & MQTT Connection v6
 *
 * Demo of:
 * - Connecting to a Wi-Fi Network.
 * - Connecting to MQTT after successfully connecting to Wi-Fi
 * - Publishing on MQTT connection
 * - Getting air quality value to publish
 *
 * Filename:        esp32_wifi_mqtt_connect_v2.ino
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
#include <ArduinoJson.h>
#include "Air_Quality_Sensor.h"

#define DEBUG 1
#include "debug.h"
#include "secrets.h"

/**--------------------------------------------------------------------------
 * Declarations 
 *---------------------------------------------------------------------------*/

#define MAX_ATTEMPTS 5
#define RETRY_PERIOD 500
#define RETRY_BACKOFF 50
#define MICRO_S_TO_S_FACTOR 1000000 /* microseconds per second */
#define TIME_TO_SLEEP 10            /* seconds */
#define SENSOR_WARM_UP 20           /* seconds */

// Constants


// Variables
int counter = 0;

AirQualitySensor sensor(35);
WiFiClient wifiClient;

const char clientid[] PROGMEM = IO_CLIENTNAME;  // Set ESP32 Name (Used as MQTT client ID)

Adafruit_MQTT_Client mqtt(&wifiClient, IO_BROKER, IO_PORT, IO_USERNAME, IO_KEY);

// Connect to MQTT Topics
Adafruit_MQTT_Publish pubData = Adafruit_MQTT_Publish(&mqtt, IO_DATA_PUB);
Adafruit_MQTT_Publish pubAnnounce = Adafruit_MQTT_Publish(&mqtt, IO_ANNOUNCE);
Adafruit_MQTT_Subscribe subCommand = Adafruit_MQTT_Subscribe(&mqtt, IO_COMMAND);


/**--------------------------------------------------------------------------
 * Hardware/Software Configuration
 *---------------------------------------------------------------------------*/
// Setting Up Hardware

void setup() {

  DEBUG_BEGIN(9600);  // Higher serial port speed 115200
  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("");

  print_wakeup_reason();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * MICRO_S_TO_S_FACTOR);
  DEBUG_PRINTLN("Sleeping every " + String(TIME_TO_SLEEP) + "seconds.");

  int connected_wifi = initWiFi();  // Call the Connect to Wi-Fi function

  if (!connected_wifi) {
    DEBUG_PRINTLN("No Wi-fi Connection");
  } else {

    wifiDetails();

    int connected_mqtt = initMQTT();
    if (connected_mqtt) {
      DEBUG_PRINTLN("MQTT Connection Successful");
      pubAnnounce.publish("Connected:" IO_CLIENTNAME);
    } else {
      DEBUG_PRINTLN("MQTT Connection Failed");
    }

    DEBUG_PRINTLN("Set-up complete");
  }
  DEBUG_PRINTLN();

  DEBUG_PRINTLN("Waiting 10 seconds for sensor to init...");
  delay(1000 * SENSOR_WARM_UP);

  if (sensor.init()) {
    DEBUG_PRINTLN("Sensor ready.");

    int quality = sensor.slope();
    int qual_value = sensor.getValue();

    int pubDataError = false;
    // JsonDocument doc;
    String output;

    // doc["device"] = IO_CLIENTNAME;
    // doc["count"] = qual_value;

    // serializeJson(doc, output);

    // Create a character string (array)
    char outputString[64];
    dtostrf(qual_value, 1, 2, outputString);

    //pubDataError = pubData.publish(output.c_str());
    pubDataError = pubData.publish(outputString);


    DEBUG_PRINT(qual_value);

#if pubDataError && DEBUG
    DEBUG_PRINTLN("Pub: Data Failed");
#else
    DEBUG_PRINTLN("Pub: Data Success");
#endif


  } else {
    DEBUG_PRINTLN("Sensor ERROR!");
  }

  DEBUG_PRINTLN("Sleepy time...")
  DEBUG_FLUSH();

  esp_deep_sleep_start();
}

/**--------------------------------------------------------------------------
 * Master/Main Loop
 *---------------------------------------------------------------------------*/
void loop() {
  /**
   * This code executes for as long as the hardware
   * is turned on, or not asleep
   */
}

/**--------------------------------------------------------------------------
 * Functions & Helper Code
 *---------------------------------------------------------------------------*/
void wifiDetails() {
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
  int attempts = 0;          // current attempt count
  uint8_t wifiStatus = 255;  // set status to "unknown"

  // Set ESP32 into Station mode (Wi-Fi client)
  // and disconnect any existing connections
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(10);

  // Set Wi-Fi Hostname & Start Wi-Fi Connection
  WiFi.setHostname(hostname);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  DEBUG_PRINTLN("Connecting to Wi-Fi ");

  while (wifiStatus != WL_CONNECTED && attempts < MAX_ATTEMPTS) {
    attempts++;
    delay(RETRY_PERIOD + RETRY_BACKOFF * attempts);

    wifiStatus = WiFi.status();
    DEBUG_PRINT("CNCT #");
    DEBUG_PRINT(attempts);
    wiFiErrors(wifiStatus);
    DEBUG_PRINTLN("");
    DEBUG_PRINTLN("");
  }

  return attempts < MAX_ATTEMPTS && wifiStatus == WL_CONNECTED;
}

bool initMQTT() {
  int attempts = 0;
  uint8_t mqttConnectionResult;

  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("Connecting to MQTT Broker/Server: ");

  mqttConnectionResult = mqtt.connect();
  while (mqttConnectionResult != 0 && attempts < MAX_ATTEMPTS) {
    delay(RETRY_PERIOD + RETRY_BACKOFF * attempts);
    attempts++;

    DEBUG_PRINT("CNCT #");
    DEBUG_PRINTLN(attempts);
    DEBUG_PRINT(mqttConnectionResult);
    mqttErrors(mqttConnectionResult);
    mqtt.disconnect();

    mqttConnectionResult = mqtt.connect();
  }

  DEBUG_PRINT("CNCT #");
  DEBUG_PRINT(attempts);
  mqttErrors(mqttConnectionResult);
  DEBUG_PRINTLN("");
  return attempts < MAX_ATTEMPTS && !mqttConnectionResult;
}

void wiFiErrors(uint8_t errorNumber) {
  // https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/#4
  switch (errorNumber) {
    case WL_IDLE_STATUS:
      {
        DEBUG_PRINTLN("Temporary status on Wi-Fi Begin");
        break;
      }
    case WL_NO_SSID_AVAIL:
      {
        DEBUG_PRINTLN("No SSID are available");
        break;
      }
    case WL_SCAN_COMPLETED:
      {
        DEBUG_PRINTLN("Scan of networks is complete");
        break;
      }
    case WL_CONNECTED:
      {
        DEBUG_PRINTLN("Connected to Wi-Fi");
        break;
      }
    case WL_CONNECT_FAILED:
      {
        DEBUG_PRINTLN("Wi-Fi Connection failed");
        break;
      }
    case WL_CONNECTION_LOST:
      {
        DEBUG_PRINTLN("Wi-Fi Connection lost");
        break;
      }
    case WL_DISCONNECTED:
      {
        DEBUG_PRINTLN("Wi-Fi Disconnected");
        break;
      }
    default:
      {
        DEBUG_PRINTLN("Unknown Wi-Fi Error.");
        break;
      }
  }
}

void mqttErrors(uint8_t errorNumber) {
  // http://www.steves-internet-guide.com/client-connections-python-mqtt/
  switch (errorNumber) {
    case 0:
      {
        DEBUG_PRINTLN("MQTT Connection successful");
        break;
      }
    case 1:
      {
        DEBUG_PRINTLN("MQTT Connection refused – incorrect protocol version");
        break;
      }
    case 2:
      {
        DEBUG_PRINTLN("MQTT Connection refused – invalid client identifier");
        break;
      }
    case 3:
      {
        DEBUG_PRINTLN("MQTT Connection refused – server unavailable");
        break;
      }
    case 4:
      {
        DEBUG_PRINTLN("MQTT Connection refused – bad username or password");
        break;
      }
    case 5:
      {
        DEBUG_PRINTLN("MQTT Connection refused – not authorised");
        break;
      }
    case 6 ... 255:
      {
        DEBUG_PRINTLN("MQTT Currently unused.");
        break;
      }
    default:
      {
        DEBUG_PRINTLN("MQTT Unknown error.");
        break;
      }
  }
}


void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeupReason;

  wakeupReason = esp_sleep_get_wakeup_cause();

  switch (wakeupReason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      DEBUG_PRINTLN("Wakeup caused by external signal using RTC_IO");
      break;
    case ESP_SLEEP_WAKEUP_EXT1:
      DEBUG_PRINTLN("Wakeup caused by external signal using RTC_CNTL");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      DEBUG_PRINTLN("Wakeup caused by timer");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      DEBUG_PRINTLN("Wakeup caused by touchpad");
      break;
    case ESP_SLEEP_WAKEUP_ULP:
      DEBUG_PRINTLN("Wakeup caused by ULP program");
      break;
    default:
      Serial.printf("Wakeup not caused by deep sleep: %d", wakeupReason);
      break;
  }
}


void print_wakeup_touchpad() {
  int wakeupTouch = esp_sleep_get_touchpad_wakeup_status();

#if CONFIG_IDF_TARGET_ESP32
  switch (wakeupTouch) {
    case 0:
      DEBUG_PRINTLN("Touch detected on GPIO 4");
      break;
    case 1:
      DEBUG_PRINTLN("Touch detected on GPIO 0");
      break;
    case 2:
      DEBUG_PRINTLN("Touch detected on GPIO 2");
      break;
    case 3:
      DEBUG_PRINTLN("Touch detected on GPIO 15");
      break;
    case 4:
      DEBUG_PRINTLN("Touch detected on GPIO 13");
      break;
    case 5:
      DEBUG_PRINTLN("Touch detected on GPIO 12");
      break;
    case 6:
      DEBUG_PRINTLN("Touch detected on GPIO 14");
      break;
    case 7:
      DEBUG_PRINTLN("Touch detected on GPIO 27");
      break;
    case 8:
      DEBUG_PRINTLN("Touch detected on GPIO 33");
      break;
    case 9:
      DEBUG_PRINTLN("Touch detected on GPIO 32");
      break;
    default:
      DEBUG_PRINTLN("Wakeup not by touchpad");
      break;
  }
#else
  if (wakeupTouch < TOUCH_PAD_MAX) {
    Serial.printf("Touch detected on GPIO %d\n", touchPin);
  } else {
    DEBUG_PRINTLN("Wakeup not by touchpad");
  }
#endif
}
