/**
 * ESP32 WiFi Connection
 *
 * See also: https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
 */

#include <WiFi.h>

#define RETRY_PERIOD 1000

const char* ssid = "WIFISSID";
const char* password = "PASSWORD";

void setup() {
  Serial.begin(115200);
  wiFiConnect();

}

void loop() {
  // put your main code here, to run repeatedly:
}

void wiFiConnect() {

  // Configure WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");

  // Loop until connected, delaying by 
  // RETRY_PERIOD between attempts
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(RETRY_PERIOD);
  }

  // Output connection details
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
