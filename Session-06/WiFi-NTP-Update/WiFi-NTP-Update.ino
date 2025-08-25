/**
 * ESP32 WiFi Connection
 *
 * See also: https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
 */

#include <WiFi.h>
#include "WiFiUdp.h" 
#include "NTP.h"

#define RETRY_PERIOD 1000

const char* ssid = "NMT-IoT";
const char* password = "Do Not Share M3!";

WiFiUDP wifiUdp;
NTP ntp(wifiUdp);

void setup() {
  Serial.begin(115200);
  wiFiConnect();

ntp.ruleDST("CEST", Last, Sun, Mar, 2, 120); // last sunday in march 2:00, timetone +120min (+1 GMT + 1h summertime offset)
  ntp.ruleSTD("CET", Last, Sun, Oct, 3, 60); // last sunday in october 3:00, timezone +60min (+1 GMT)
  ntp.begin();
  Serial.println("start NTP");

}

void loop() {
  // put your main code here, to run repeatedly:

    ntp.update();
  Serial.println(ntp.formattedTime("%d. %B %Y")); // dd. Mmm yyyy
  Serial.println(ntp.formattedTime("%A %T")); // Www hh:mm:ss
  delay(1000);

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
