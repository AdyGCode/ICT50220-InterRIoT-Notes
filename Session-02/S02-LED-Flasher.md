# LED Flasher

## Components
| Name       | Quantity | Component      |
| ---------- | -------- | -------------- |
| Uno_R3_1   | 1        | Arduino Uno R3 |
| RED_LED_1  | 1        | Red LED        |
| RES_1      | 1        | 330 Ω Resistor |


## Circuit



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
