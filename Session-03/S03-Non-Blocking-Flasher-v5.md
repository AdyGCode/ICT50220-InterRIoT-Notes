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

# Non-Blocking Flasher v5

This non-blocking flasher allows for the on and off times to be different.

It also allows for a push button to be used, and trigger a different action.

## Components
| Name      | Quantity | Component      |
| --------- | -------- | -------------- |
| Uno_R3_1  | 1        | Arduino Uno R3 |
| RED_LED_1 | 1        | Red LED        |
| RES_1     | 1        | 330 Ω Resistor |
| BUTTON_1  | 1        | Push Button    |


## Circuit

![](../assets/CleanShot%202024-07-29%20at%2020.35.18@2x.webp)

## Code

```cpp
/**
 * ------------------------------------------
 * Multi-Tasking Arduino
 * 
 * Arduinos do not have Multitasking, so we need to 
 * simulate it. It relised on *cooperation* between 
 * the tasks. That is they must not hog the processor.
 * 
 * Name: 	 YOUR NAME
 *
 * Year: 	 XXXX
 * Semester: X
 * ------------------------------------------ 
 **/
 
/**
 * Imports
 */


/**
 * Macros


/**
 * Constants & Variables
 */
const char LED_BLUE_1 = 12;
const char BUTTON_PIN = 8;
const int PERIOD_ON = 500;
const int PERIOD_OFF = 1000;

bool pressed = false;
bool ledState = false;

 // use millis when looking at time differences 
 // of over 16ms 
long previousTime = millis();

/**
 * Set Up Function (called on power up/reset/restart)
 */
void setup()
{
	pinMode(LED_BLUE_1, OUTPUT);
    Serial.begin(9600);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
  	digitalWrite(LED_BLUE_1, ledState);
}

/**
 * Main program loop
 */
void loop()
{
 	long elapsedTime = millis() - previousTime;
  	previousTime = previousTime + elapsedTime;
      
	readButton(BUTTON_PIN);
	blink(elapsedTime);
}

/**
 * Blinks an LED, with ON and OFF times being different
 * and does not block the MCU
 */
void blink(long elapsedTimeMS) {
	// a static variable is not re-initialised 
	// on each function call
  	static long ledTime = 0;
  	static int period = PERIOD_OFF;
  
  	ledTime += elapsedTimeMS;
  
  	if (ledTime>= period){
    	ledTime -= period;
      	period = ledState ? PERIOD_ON : PERIOD_OFF;

      	ledState = !ledState;
  		digitalWrite(LED_BLUE_1, ledState);
  	}
}

/**
 * Read the Push Button state and perform an action.
 */
void readButton(char buttonPin){
  	bool currentState = digitalRead(buttonPin);
  
  	if (currentState == pressed){
    	Serial.println("Hello");

    	while (digitalRead(buttonPin) == pressed) {
			// Do Nothing
    	}
  	}
}
```


