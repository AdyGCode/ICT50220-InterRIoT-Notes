# Non-Blocking Flasher

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
#define PERIOD		  1000

int currentTime = 0;
int previousTime = 0;
int timeDiff = 0;
int ledState = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
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
  
}
```