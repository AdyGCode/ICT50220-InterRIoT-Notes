---
theme: default
paginate: true
footer: © Copyright 2024, Adrian Gould & NM TAFE
header: "![NMTAFE](../images/Black-Red-Banner.svg)"
auto-scaling: true
size: 4k
color: "#ccc"
backgroundColor: "#060606"
tags: 
  - Internet of Things
  - InterRIoT
  - IoT
  - Robotics
  - Python
  - Arduino
  - ESP-32
  - C
  - C++

date created: 03 July 2024
date modified: 10 July 2024
---

# Combining NTP and LCD

The next step is to use NTP and the LCD together...

# Code

We will not explain the code in detail as we already have seen the useful parts and had them explained in
- [S06-LCD-16x2](S06-LCD-16x2.md), and
- [S06-NTP-Time-Update](S06-NTP-Time-Update.md)

```c
/**
 * LCD Display Net Time Demo
 *
 * Uses I2C to control the LCD.
 * Based on Freenove example.
 *
 * Libraries: Arduino IDE shortcut - CTRL+SHIFT+I
 * - LiquidCrystal_I2C [Frank de Brabander]
 * - Wire
 * - TimeLib
 * - WiFi
 * - NTP [Stefan Staub https://github.com/sstaub/NTP]
 *
 * Wiring:
 * - LCD PIN  JUMPER COLOUR   ESP PIN
 * - 1        Brown           GND
 * - 2        Red             5V
 * - 3        Orange          13
 * - 4        Yellow          14
 *
 */  

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <time.h>
#include <WiFi.h>
#include "WiFiUdp.h"
#include "NTP.h"

#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 1000
#define MAX_ATTEMPTS 5

#define SDA 13  //Define SDA pins
#define SCL 14  //Define SCL pins

/*
 * I2C Chip: PCF8574T   0x27
 *           PCF8574AT  0x3F
 */
#define PCF8574T   0x27
#define PCF8574AT  0x3F 
#define LCD_I2C 0x27
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#define UPDATE_PERIOD 1000

LiquidCrystal_I2C lcd(LCD_I2C, LCD_WIDTH, LCD_HEIGHT);

/* Create the UDP Wi-Fi connection and hook 
 * the NTP requests into UDP.
 */
WiFiUDP wifiUdp; 
NTP ntp(wifiUdp);
  
unsigned long previousTime = 0;
unsigned long currentTime = 0;
int interval = UPDATE_PERIOD;
char buff[16];
bool connected;

const char* ssid     = "NMT-IoT";
const char* password = "Do Not Share M3!";

void setup() {
  Wire.begin(SDA, SCL);  // attach the I2C pin
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Wi-Fi Time");

  connected = wiFiConnect();

  lcd.setCursor(0, 1);

  if (connected) {
    lcd.print("Connected       ");

	// Perth, Australia is 8 hours ahead of GMT
	// and does NOT have DST.
    ntp.timeZone(8,0);
    ntp.isDST(false);

    ntp.begin();
    ntp.update();

  } else {
    lcd.print("Connect Fail  :(");
  }

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {

  if (connected){
    currentTime = millis();

    if ((currentTime - previousTime) >= UPDATE_PERIOD) {
      printLocalTime();
      previousTime = currentTime;
    }
  }
}

void printLocalTime() {
  lcd.setCursor(0, 1);
  lcd.print(ntp.formattedTime("%d %b, %T"));
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
```


[Back to Session 06...](ReadMe.md)
