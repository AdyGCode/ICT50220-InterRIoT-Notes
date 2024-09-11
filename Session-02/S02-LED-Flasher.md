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

# LED Flasher

## Components
| Name       | Quantity | Component      |
| ---------- | -------- | -------------- |
| Uno_R3_1   | 1        | Arduino Uno R3 |
| RED_LED_1  | 1        | Red LED        |
| RES_1      | 1        | 330 Ω Resistor |


## Circuit

The circuit on an Arduino Uno R3 is shown below.

![](CleanShot%202024-07-29%20at%2020.35.18@2x.png)

## Code

```cpp
#define RED_LED_1		13
#define PERIOD		  1000

void setup()
{
  pinMode(RED_LED_1, OUTPUT);
  digitalWrite(RED_LED_1, LOW);
}

void loop()
{
    digitalWrite(RED_LED_1, ledState);
    delay(PERIOD);
    digitalWrite(RED_LED_1, LOW); 
    delay(PERIOD);
}
```

This code is said to be blocking as the `delay` function stops the code from continuing until the time `PERIOD` (in milliseconds) has expired.

