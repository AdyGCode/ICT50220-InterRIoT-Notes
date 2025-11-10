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

# LED Flasher & Pushbutton

## Components
| Name      | Quantity | Component                 |
| --------- | -------- | ------------------------- |
| Uno_R3_1  | 1        | Arduino Uno R3            |
| RED_LED_1 | 1        | Red LED                   |
| RES_1     | 1        | 330 Ω Resistor            |
| PB_1      | 1        | Pushbutton (Push to Make) |


## Circuit

![img.webp](flashing-led-with-push-button-1.webp)

## Code

```cpp
/**
 * Toggle LED with Push button
 * 
 * Filename:  n/a TinkerCAD
 * Author:    Adrian Gould <adrian.gould@nmtafe.wa.edu.au>
 * Version:   1.0
 */

// Include Libraries


// Constants / Macros
const bool    DEBUG     = true;

const uint8_t RED_LED_1 = 13;
const uint8_t PB_1      = 12;
const uint8_t PERIOD	= 1000;


// Global Variables
int buttonState = LOW;
int ledState = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(RED_LED_1, OUTPUT);
  pinMode(PB_1, INPUT);
  digitalWrite(RED_LED_1, LOW);
}

void loop()
{

	buttonState = digitalRead(PB_1);
	
	if (buttonState == HIGH) {
      	ledState = !ledState;
      
        if (DEBUG){
            Serial.print(buttonState);
      	    Serial.print(" ");
      	    Serial.println(ledState);
        }
      
    	digitalWrite(RED_LED_1, ledState);	    

	} 

}
```

When the push button is pressed the LED is turned on. When the button is next pressed the LED is turned off.

**Question:** ?

