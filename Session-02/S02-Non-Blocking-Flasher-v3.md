# Non-Blocking Flasher

This non-blocking flasher allows for the on and off times to be different.

## Components
| Name      | Quantity | Component      |
| --------- | -------- | -------------- |
| Uno_R3_1  | 1        | Arduino Uno R3 |
| RED_LED_1 | 1        | Red LED        |
| RES_1     | 1        | 330 Ω Resistor |


## Circuit

![](CleanShot%202024-07-29%20at%2020.35.18@2x.png)

## Code

```cpp
#define RED_LED_1		13
#define PERIOD_ON		1000
#define PERIOD_OFF		2000

unsigned long previousTime = 0;
int interval = PERIOD_ON;
boolean ledState = true;

void setup()
{
  pinMode(RED_LED_1, OUTPUT);
  digitalWrite(RED_LED_1, ledState);
}

void loop()
{

  digitalWrite(RED_LED_1, ledState);
  
  unsigned long currentTime = millis();
  unsigned long timeDiff = currentTime - previousTime;
  
  if (timeDiff >= 1000){
      if (ledState) {
        interval = offTime;
      else {
        interval = onTime;
     }
  
    ledState = !ledState;
    previousTime = currentTime;
  }
  
}
```


[Arduino: Independent On-Off Times with Millis() - Bald Engineer](https://www.baldengineer.com/millis-ind-on-off-times.html)
