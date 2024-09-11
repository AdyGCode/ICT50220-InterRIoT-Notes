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

# Non-Blocking Flasher V2

This flasher blinks a red LED and then blinks the blue LED when the pushbutton is pressed and held.

## Components
| Name         | Quantity | Component      |
| ------------ | -------- | -------------- |
| Uno_R3_1     | 1        | Arduino Uno R3 |
| RED_LED_1    | 1        | Red LED        |
| RES_1, RES_2 | 2        | 330 Ω Resistor |
| PB_1         | 1        | Pushbutton     |
| RES_3        | 1        | 10 kΩ Resistor |
| BLUE_LED_1   | 1        | Blue LED       |

## Circuit

![LED Flasher Circuit](../assets/Session-02-20240724162543.png)

## Code

```cpp
#define RED_LED_1		13
#define BLUE_LED_1		12
#define PB_1			 2
#define PERIOD		  1000

int currentTime = 0;
int previousTime = 0;
int timeDiff = 0;
int ledState = LOW;
int buttonState = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PB_1, INPUT);
  digitalWrite(RED_LED_1, ledState);
}

void loop()
{
  currentTime = millis();
  
  timeDiff = currentTime - previousTime;
  if (timeDiff > 1000){
    Serial.println(ledState);
    // ledState = ledState == LOW ? HIGH : LOW;
    ledState = !ledState;
    digitalWrite(RED_LED_1, ledState);
    previousTime = currentTime;
  }
  
  buttonState = digitalRead(PB_1);
  if (buttonState == HIGH) {
    digitalWrite(BLUE_LED_1, HIGH);
  } else {
    digitalWrite(BLUE_LED_1, LOW); 
  }
}
```