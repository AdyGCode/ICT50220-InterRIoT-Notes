/**
 * ESP32 WiFi & MQTT with error messages
 * 
 * Project: WiFi-MQTT-With-Error-Messages
 *
 * Requires:
 *   - Adafruit MQTT
 *   - Adafruit MQTT Client
 *   - Adafruit account (https://adafruit.com)
 */

#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>


#define IO_USERNAME ""
#define IO_KEY ""
#define IO_SERVER "127.0.0.1"
#define IO_SERVERPORT 1883

// #define IO_USERNAME "ADAFRUIT_USERNAME"
// #define IO_KEY "ADAFRUIT_KEY"
// #define IO_SERVER "ADAFRUIT_SERVER_URI"
// #define IO_SERVERPORT ADAFRUIT_IO_PORT_NUMBER

#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 250
#define MAX_ATTEMPTS 5

const char* ssid = "NMT-IoT";
const char* password = "Its!Working";
// const char* ssid = "WIFI_SSID";
// const char* password = "WIFI_PASSWORD";

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_SERVERPORT, IO_USERNAME, IO_KEY);

void setup() {
  Serial.begin(115200);

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
  uint8_t wifiStatus = 255;

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  wifiStatus = WiFi.status();
  while (wifiStatus != WL_CONNECTED && attempts <= MAX_ATTEMPTS) {
    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);

    wifiStatus = WiFi.status();
    if (wifiStatus != WL_CONNECTED) {
      Serial.print("CNCT #");
      Serial.print(attempts);
      Serial.print(": ");
      Serial.print(wifiStatus);
      Serial.print(" ");
      wiFiErrors(wifiStatus);
    }
    attempts++;
  }

  return attempts < MAX_ATTEMPTS;
}

bool mqttConnect() {
  uint8_t attempts = 0;         // Unsigned 8 bit integer
  int8_t mqttConnectionResult;  // signed 8 bit integer

  Serial.println("Connecting to MQTT...");
  mqttConnectionResult = 255;

  while (mqttConnectionResult != 0 && attempts <= MAX_ATTEMPTS) {
    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);
    attempts++;

    if (mqttConnectionResult != 0) {
      Serial.print("CNCT #");
      Serial.print(attempts);
      Serial.print(" ");
      mqttErrors(mqttConnectionResult);
      mqtt.disconnect();
    }
    mqttConnectionResult = mqtt.connect();
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

void wiFiErrors(uint8_t errorNumber) {
  // https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/#4
  switch (errorNumber) {
    case WL_IDLE_STATUS:
      {
        Serial.println("Temporary status on Wi-Fi Begin");
        break;
      }
    case WL_NO_SSID_AVAIL:
      {
        Serial.println("No SSID are available");
        break;
      }
    case WL_SCAN_COMPLETED:
      {
        Serial.println("Scan of networks is complete");
        break;
      }
    case WL_CONNECTED:
      {
        Serial.println("Connected to Wi-Fi");
        break;
      }
    case WL_CONNECT_FAILED:
      {
        Serial.println("Wi-Fi Connection failed");
        break;
      }
    case WL_CONNECTION_LOST:
      {
        Serial.println("Wi-Fi Connection lost");
        break;
      }
    case WL_DISCONNECTED:
      {
        Serial.println("Wi-Fi Disconnected");
        break;
      }
    default:
      {
        Serial.println("Unknown Wi-Fi Error.");
        break;
      }
  }
}

void mqttErrors(uint8_t errorNumber) {
  // http://www.steves-internet-guide.com/client-connections-python-mqtt/
  switch (errorNumber) {
    case 0:
      {
        Serial.println("MQTT Connection successful");
        break;
      }
    case 1:
      {
        Serial.println("MQTT Connection refused – incorrect protocol version");
        break;
      }
    case 2:
      {
        Serial.println("MQTT Connection refused – invalid client identifier");
        break;
      }
    case 3:
      {
        Serial.println("MQTT Connection refused – server unavailable");
        break;
      }
    case 4:
      {
        Serial.println("MQTT Connection refused – bad username or password");
        break;
      }
    case 5:
      {
        Serial.println("MQTT Connection refused – not authorised");
        break;
      }
    case 6 - 255:
      {
        Serial.println("MQTT Currently unused.");
        break;
      }
    default:
      {
        Serial.println("MQTT Unknown error.");
        break;
      }
  }
}