# Operating the 16x2 LCD



Code:
```c
/**

 * LCD Display example
 *
 * Uses I2C to control the LCD.
 * Based on Freenove example.
 *
 * Libraries:
 * - LiquidCrystal_I2C
 * - Wire

1 gnd Brown-
2 vdd Red-
3 sda Orange-
4 scl Yellow-
 */

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SDA 13  //Define SDA pins
#define SCL 14  //Define SCL pins

/*
 * I2C Chip: PCF8574T   0x27
 *           PCF8574AT  0x3F
 */
#define LCD_I2C 0x27
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

 
#define UPDATE_PERIOD 100
  
LiquidCrystal_I2C lcd(LCD_I2C, LCD_WIDTH, LCD_HEIGHT);
unsigned long previousTime = 0;
unsigned long currentTime = 0;
int interval = UPDATE_PERIOD;
char buff[16];
  
 
void setup() {
  
  Wire.begin(SDA, SCL);  // attach the IIC pin
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  
  lcd.init();                 // LCD driver initialization
  
  lcd.backlight();            // Open the backlight
  
  lcd.setCursor(0, 0);        // Move the cursor to row 0, column 0
  
  lcd.print("LCD I2C Demo");  // The print content is displayed on the LCD
}
  
void loop() {
  currentTime = millis();
  
  if ((currentTime - previousTime) >= UPDATE_PERIOD) {
    // Display outpout on line 2 of the LCD 
    // starting at column 1
    lcd.setCursor(0, 1);
    sprintf(buff, "Timer: %6.1f", ((float)currentTime) / 1000.0);
    lcd.printf(buff);
  
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
```


[Back to Session 06...](ReadMe.md)
