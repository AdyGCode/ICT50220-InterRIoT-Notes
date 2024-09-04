/**
 * ESP32 WiFi with Connection Confirmation via LED
 *
 */

#include <WiFi.h>

#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 500
#define MAX_ATTEMPTS 5

#define LED_ON_PERIOD 100
#define LED_RED_1   18


const char* ssid = "NMT-IoT";
const char* password = "Do Not Share M3!";

void setup() {
  Serial.begin(115200);

  pinMode(LED_RED_1, OUTPUT);

  bool connected = wiFiConnect();

  if (connected) {
    Serial.println();
    Serial.println("Connected");
    wiFiDetails();
    flashLed(LED_RED_1, LED_ON_PERIOD);
  } else {
    Serial.println();
    Serial.println("Connection Failed");
  }
}

void loop() {
  


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

void flashLed(int ledPin, int timeOn){
  digitalWrite(ledPin, HIGH);
  delay(timeOn);
  digitalWrite(ledPin, LOW);
}
