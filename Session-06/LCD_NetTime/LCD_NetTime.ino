/**
 * LCD Display example
 *
 * Uses I2C to control the LCD.
 * Based on Freenove example.
 * 
 * Libraries:
 * - LiquidCrystal_I2C
 * - Wire
 * - TimeLib
 * - WiFi
 */

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "time.h"
#include <WiFi.h>

#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 1000
#define MAX_ATTEMPTS 5

#define SDA 13  //Define SDA pins
#define SCL 14  //Define SCL pins

/*
 * I2C Chip: PCF8574T   0x27
 *           PCF8574AT  0x3F
 */
#define LCD_I2C 0x27
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#define UPDATE_PERIOD 1000

LiquidCrystal_I2C lcd(LCD_I2C, LCD_WIDTH, LCD_HEIGHT);

unsigned long previousTime = 0;
unsigned long currentTime = 0;

int interval = UPDATE_PERIOD;

char buff[16];

const char* ssid     = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

void setup() {

  Wire.begin(SDA, SCL);  // attach the IIC pin
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Wi-Fi Time");

  bool connected = wiFiConnect();
  lcd.setCursor(0, 1);
  if (connected) {
    lcd.print("Connected       ");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  } else {
    lcd.print("Connect Fail    ");
  }
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {
  currentTime = millis();

  if ((currentTime - previousTime) >= UPDATE_PERIOD) {
    printLocalTime();
    previousTime = currentTime;
  }
}

bool i2CAddrTest(uint8_t addr) {
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}

bool wiFiConnect() {
  int attempts = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  lcd.setCursor(0, 1);
  lcd.print("Connecting       ");
  delay(RETRY_PERIOD);
  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPTS) {

    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);
    lcd.setCursor(12, 1);
    lcd.print(attempts+1);
    attempts++;

  }

  return attempts < MAX_ATTEMPTS;
}


void printLocalTime() {
  lcd.setCursor(0, 1);
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    lcd.print("Get Time Fail");
    return;
  }

  uint hour = timeinfo.tm_hour;
  uint min = timeinfo.tm_min;
  uint sec = timeinfo.tm_sec;
  sprintf(buff, "%2d:%2d:%2d ", hour, min, sec);
  lcd.print(buff);

}
