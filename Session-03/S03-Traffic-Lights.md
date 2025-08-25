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

# Traffic Lights

This simulation provides the basics of a UK traffic light sequence.

In the UK the traffic light go:
- Red
- Red, Amber (Prepare to go)
- Green
- Amber (Prepare to stop)
- Red

Traffic lights are different across the world, but this sequence is quite a nice one to do as it has more steps.

The components listed also include a switch and LEDs for a pedestrian crossing to be added.

## Components
| Name                              | Quantity | Component      |
| --------------------------------- | -------- | -------------- |
| Uno_R3_1                          | 1        | Arduino Uno R3 |
| RED_LED_1, RED_LED_2              | 2        | Red LED        |
| RES_1, RES_2, RES_3, RES_4, RES_5 | 2        | 330 Ω Resistor |
| PB_1                              | 1        | Pushbutton     |
| RES_6                             | 1        | 10 kΩ Resistor |
| GREEN_LED_1, GREEN_LED_2          | 2        | Green LED      |
| AMBER_LED_1                       | 1        | Yellow LED     |

## Circuit

![Session-02-20240724163629.png](../assets/Session-02-20240724163629.png)

## Code
This code is functional, but it uses blocking calls.

```cpp
/* ------------------------------------------ *
 *
 * Traffic Light Simulator 1
 * 
 * This simulator is based on the UK traffic
 * light and pedestrian crossing sequence.
 * As a result there is a Red-Amber Phase before
 * the Green is lit.
 * 
 * Name: 	 YOUR NAME
 *
 * Year: 	 XXXX
 * Semester: X
 *
 * ------------------------------------------ */
// Imports

// Macros

// Traffic Lights
#define RED_LED_1     13
#define AMBER_LED_1   12
#define GREEN_LED_1    8

// Pedestrian Crossing Lights & Button
#define RED_LED_2      7
#define GREEN_LED_2    4
#define PB_1		   2

// Variables

int buttonState = LOW;

// Set up device
void setup()
{
  pinMode(RED_LED_1, OUTPUT);
  pinMode(RED_LED_2, OUTPUT);
  pinMode(AMBER_LED_1, OUTPUT);
  pinMode(GREEN_LED_1, OUTPUT);
  pinMode(GREEN_LED_2, OUTPUT);
  
  pinMode(PB_1, INPUT);
  
  ledOn(RED_LED_1);
  ledOn(RED_LED_2);
  ledOff(AMBER_LED_1);
  ledOff(GREEN_LED_1);
  ledOff(GREEN_LED_2);
}

// Run loop
void loop()
{
  stop(5);
  prepareToGo(1);
  go(8);
  prepareToStop(2);
  buttonState = digitalRead(PB_1);
  if (buttonState == HIGH) {
    ledOn(RED_LED_1);
    ledOff(AMBER_LED_1);
    delay(2000);
    ledOff(RED_LED_2);
    ledOn(GREEN_LED_2);
    delay(5000);
    ledOn(RED_LED_2);
    ledOff(GREEN_LED_2);
  }
}

void stop(int seconds) {
  ledOn(RED_LED_1);
  ledOff(AMBER_LED_1);
  delay(seconds*1000);
}

void prepareToGo(int seconds)
{
  ledOn(AMBER_LED_1);
  delay(seconds * 1000);
}

void prepareToStop(int seconds)
{
  ledOn(AMBER_LED_1);
  ledOff(GREEN_LED_1);
  delay(seconds * 1000);
}

void go(int seconds) 
{
  ledOn(GREEN_LED_1);
  ledOff(RED_LED_1);
  ledOff(AMBER_LED_1);
  delay(seconds * 1000);
}

void ledOff(int ledPin){
  digitalWrite(ledPin, LOW);
}


void ledOn(int ledPin){
  digitalWrite(ledPin, HIGH);
}
```

