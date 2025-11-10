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

# Session 02 Review Exercises 

```table-of-contents
title: # Contents
style: nestedList
minLevel: 0
maxLevel: 3
includeLinks: true
```

---

# Getting Ready

If you have not done so, follow the instructions in [S01 Notes And Review Exercises](S01-Notes-And-Review-Exercises.md) to set up a Markdown based Notes Repository.

Adrian and other lecturers use Obsidian as a markdown editor and note organisation tool every day. In fact these notes are created using Obsidian.

# Knowledge Exercises

For each of the exercises, make sure you do the following:

- Perform the research using common search engine techniques
- DO NOT use AI systems
- For each example located, ensure you note a correctly formed APAP v6 or APA v7 bibliographic reference and add to a document.

Create a new Markdown document in the `session-01` folder of your Notes Repository, and call it `exercises.md`.

For each exercise below, add suitable headings.

We give an example below:

```markdown
# Oscilloscopes

## Specifications

- Item ...
	- Details ...
	- Details ...
- etc. ...

## Prices

| Manufacturer | model | Price $AU |
|--------------|-------------|-----------|
| Some company | XYZ123 | $1235 |

```

This displays as:

![](../Pasted%20image%2020250725161528.webp)



## Oscilloscope: specifications (exercise)

- Research the following oscilloscope specifications:
    - Bandwidth
    - Digital vs analogue types
    - Number of channels
    - Sampling rate
    - Rise time
    - Maximum input voltage
    - Resolution
    - Vertical sensitivity
    - Time base
    - Input impedance

- What is the typical cost for an Oscilloscope?


## Signal generator: specifications (exercise)

- Research the following signal generator specifications:
    - Maximum frequency
    - Number of channels
    - Sample rate
    - Resolution
    - Frequency stability
    - Modulation functions (e.g., FM, PSK, …)

- Q: What is the typical cost?

## Spectrum analyser: specifications (exercise)

- Research the following signal generator specifications:
    - Center frequency
    - Frequency span
    - Resolution bandwidth
    - Sample detection
    - Peak detection
    - Average detection
    - Sensitivity

- Q: What is the typical cost?


## Exercise: Multimeters

Locate and price two multimeters.

Try to find two different examples, possibly one "low cost" and one "high cost" example.

## Exercise: what else?

- We have covered the most common laboratory tools that any electronics lab should have
- What other (more exotic) instruments can you find?


# "Practical" Exercises

For each of the exercises, make sure you do the following:

- Copy code to a backup document
- Add a comment with the link to your TinkerCAD circuit

## Exercise 1  
  
This program will not work...  
  
```cpp 
String a = "The result is: ";  
int b = 100;  
int c = 1;  
  
void setup() {  
  Serial.begin(9600);}  
  
void loop() {  
  Serial.println(a + b + c); // Fix this line  c = c + 1;  delay(1000);}  
```  
  
Fix it, so that it displays...  
  
```  
The result is: 101  
The result is: 102  
The result is: 103  
.  
.  
.  
```  
  
## Exercise 2  
  
This is the same as the previous program, but the variable **b** is now a String.  
  
```cpp 
String a = "The result is: ";  
String b = "100";  
int c = 1;  
  
void setup() {  
  Serial.begin(9600);}  
  
void loop() {  
  Serial.println(a + b + c); 
  // Fix this line 
   c = c + 1;  
  delay(1000);
  }  
```  
  
Fix it, so that it displays the same output as before...  
  
```  
The result is: 101  
The result is: 102  
The result is: 103  
.  
.  
.  
```

## Exercise 3
  
Add conditions to the below program, so that it displays "Low" if the value of a is less than 10, "High" if the value of a is greater than 10, and "Correct" if it is exactly 10.  
  
```cpp hl_lines="10 11"  
int a = 1;  
  
void setup() {  
  Serial.begin(9600);}  
  
void loop() {  
  Serial.println(a);  
  // Write your code here.  // Don't change the other lines.  
  a = a + 1;  delay(1000);}  
```

## Exercise 4
  
The factorial of a number is the multiplication of all positive integers less than or equal to that number.  

For example, the factorial of 3 is 6 (1 x 2 x 3) and the factorial of 5 is 120 (1 x 2 x 3 x 4 x 5).  
  
Using a `for` loop, modify the program below to print out the factorial of **7**.  
  
```cpp hl_lines="8"  
void setup() {  
  Serial.begin(9600);
}  
  
void loop() {  
  int result = 0;  
  // Put your for loop here  
  Serial.println(result);  
  delay(1000);
}  
```

  
## Exercise 5
  
Write a function that takes a single `int` as parameter, and returns the cube (power of 3) of that number.  
  
## Exercise 6  
  
Make an alternate version of the previous function (use a different name), and modify it so that instead of 
returning the cube of the provided number, it will simply print it out.  
  
## Exercise 7
  
Write a program that makes the external LED and the built-in LED blink alternately.  

This means that when the built-in LED is on, the external LED should be off, and vice versa.

## Exercise 8  
  
Write a program that makes the built-in LED toggle between blinking and off when the button is pressed.
  
## Exercise 9
  
In the example in [Session 02, Intro to C Part 12](S02-Intro-to-C-Part-12.md), the brightness goes gradually 
from zero to max.  

But once it reaches max brightness, it abruptly changes back to zero brightness.  

Modify the program so that it will gradually change back from max to zero.


## Exercise 10

Create a circuit that has two LEDs (you choose the colours), and two 330 Ohm (330Ω) resistors. 

It also has a pushbutton switch and a resistor configured to 'pull down' the switch input to LOW by default.

Wire up the circuit, and write the code, using an Arduino and a small breadboard so that:

- The code is NON blocking
- The first LED starts flashing by default
- When the button is pressed (and released) again, the flashing LED toggles:
  - the currently flashing LED will stop, and
  - the other LED will flash
- The LEDs will flash at a rate of:
  - on for 500ms and
  - off for 750ms

> **Hint 1:** 
> 
> Start by solving the different on/off periods for the on and off for ONE of the LEDs.

> **Hint 2:** 
> 
> Add switch detection to check if button pressed, and to toggle a value to enable the correct LED to flash.



  
## Exercise  11
  
Using the **LED Brightness Control** circuit, modify the code so that instead of controlling the brightness of the LED, it will control how fast it blinks.  

When the potentiometer is turned to zero, the LED should blink once every `2.0` seconds.  

When the potentiometer is turned to max, the LED should blink once every`0.1` seconds.


# Recap

If you have not done so, make sure you go back over Session 01's [Notes And Review Exercises](../Session-01/S01-Notes-And-Review-Exercises.md)

