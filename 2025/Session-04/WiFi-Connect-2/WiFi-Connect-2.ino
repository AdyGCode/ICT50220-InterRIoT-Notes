/**
 * ESP32 WiFi Connection v2
 *
 * See also: https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
 */

#include <WiFi.h>

#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 250
#define MAX_ATTEMPTS 5

#define FLASH_TIME 250
#define FLASH_COUNT 5

#define LED_RED_1 19
#define LED_GREEN_1 18

#define DEBUG 1

const char* ssid = "NMT-IoT";
const char* password = "Its!Working";

void setup() {
  Serial.begin(115200);

  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);

  digitalWrite(LED_RED_1, HIGH);
  digitalWrite(LED_GREEN_1, LOW);

  bool connected = wiFiConnect();

  if (connected) {
    if (DEBUG) { Serial.println("Connected"); }
    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_GREEN_1, HIGH);
    if (DEBUG) {      wiFiDetails();    }
  } else {
    if (DEBUG) {
      Serial.println("Connection Failed");
    }
    for (int count = 0; count < FLASH_COUNT; count++) {
      delay(FLASH_TIME);
      digitalWrite(LED_RED_1, HIGH);
      delay(FLASH_TIME);
      digitalWrite(LED_RED_1, LOW);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

bool wiFiConnect() {
  int attempts = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  if (DEBUG) { Serial.println("Connecting to WiFi..."); }

  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPTS) {
    if (DEBUG) { Serial.print("."); }
    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);
    attempts++;
  }

  return attempts < MAX_ATTEMPTS;
}

void wiFiDetails() {
  if (DEBUG) {
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
}