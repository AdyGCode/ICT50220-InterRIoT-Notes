/**
 * ESP32 WiFi Connection
 *
 * See also: https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
 */

#include <WiFi.h>

#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 250
#define MAX_ATTEMPTS 5

const char* ssid = "WIFI_SSID";
const char* password = "PASSWORD_HERE";

void setup() {
  Serial.begin(9600);
  bool connected = wiFiConnect();
  if (connected) {
    Serial.println("Connected");
    wiFiDetails();
  } else {
    Serial.println("Connection Failed");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

bool wiFiConnect() {
  int attempts = 0;

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
