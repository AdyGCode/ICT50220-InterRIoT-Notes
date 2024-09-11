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



## Code

```cpp
#define RED_LED_1		13
#define PB_1             2
#define PERIOD		  1000

int buttonState = LOW;

void setup()
{
  pinMode(RED_LED_1, OUTPUT);
  pinMode(PB_1, INPUT);
  digitalWrite(RED_LED_1, LOW);
}

void loop()
{

	buttonState = digitalRead(PB_1);
	if (buttonState == HIGH) {
	    digitalWrite(RED_LED_1, ledState);
	    delay(PERIOD);
	} else {
		digitalWrite(RED_LED_1, LOW); 
	    delay(PERIOD);
    }
}

```

When the pushbutton is pressed the LED is turned on for `PERIOD` milliseconds, and if it is not pressed the LED is turned off for `PERIOD` seconds.

**Question:** What could be a problem with this circuit and code?

