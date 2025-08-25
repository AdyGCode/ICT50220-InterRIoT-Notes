/**
 * ESP32 WiFi Scanner
 *
 */
#include <WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup Completed");
}

void loop() {
  Serial.println("Scanning...");
  int networkCount = WiFi.scanNetworks();

  if (networkCount == 0) {
    Serial.println("No networks found.");
  } else {
    for (int count = 0; count < networkCount; ++count){
      Serial.print(count);
      Serial.print(": ");
      Serial.print(WiFi.SSID(count));
      Serial.print(" [");
      Serial.print(WiFi.RSSI(count));
      Serial.print("]");
      Serial.println((WiFi.encryptionType(count) == WIFI_AUTH_OPEN) ? " OPEN" : "*");
      delay(250);
    }
  }
  Serial.println("");
  delay(10000);
}
