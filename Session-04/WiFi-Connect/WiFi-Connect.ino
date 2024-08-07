/**
 * ESP32 WiFi Connection
 *
 * See also: https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
 */

#include <WiFi.h>

#define RETRY_PERIOD 1000

const char* ssid = "WIFI_SSID";
const char* password = "PASSWORD_HERE";

void setup() {
  Serial.begin(9600);
  wiFiConnect();

}

void loop() {
  // put your main code here, to run repeatedly:
}

void wiFiConnect() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(RETRY_PERIOD);
  }
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
