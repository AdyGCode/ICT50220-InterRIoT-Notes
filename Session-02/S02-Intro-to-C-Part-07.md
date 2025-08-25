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

# Introducing C/C++ for IoT

[S02-Intro-to-C-Part-06.md](S02-Intro-to-C-Part-06.md) | [S02-Intro-to-C-Part-08.md](S02-Intro-to-C-Part-08.md)

# Define Constants

In the section on **Digital Output** (under **Arduino Basics**), you will see this code for blinking an external LED
that is connected to pin 11.

```cpp 
void setup() {  
  pinMode(11, OUTPUT);}  
  
void loop() {  
  digitalWrite(11, HIGH); 
   delay(1000);  
  digitalWrite(11, LOW); 
   delay(1000);
  }  
```  

This code works just fine, but what if you need to change the wiring so that the LED is connected to pin 12 instead?

You would need to modify the highlighted lines, changing all the `11` to `12`, like this...

```cpp 
void setup() {  
  pinMode(12, OUTPUT);
}  
  
void loop() {  
  digitalWrite(12, HIGH);  
  delay(1000);  
  digitalWrite(12, LOW);  
  delay(1000);
}  
```  

As our program is rather short, and the `11` only appears 3 times, this modification isn't that hard to do.  

But what if the program is hundreds of lines long and the number `11` appears dozens of times?  

It's going to be much more tedious to manually change all the `11`, and it's also likely that you may miss out
changing one or two of them.

To avoid this problem, programmers often use `#define` to create a **constant**, like this...

```cpp
#define LED_PIN 11  
  
void setup() {  
  pinMode(LED_PIN, OUTPUT);
}  
  
void loop() {  
  digitalWrite(LED_PIN, HIGH);  
  delay(1000);  
  digitalWrite(LED_PIN, LOW);  
  delay(1000);
}  
```  

`#define LED_PIN 11`
- This defines a **constant** named `LED_PIN` and give it a value of `11`.
- When the program is compiled, the compiler will search through the entire file and replace every `LED_PIN` with `11`.

Now if you need to change the pin to `12`, you just need to modify the first line...

```cpp  
#define LED_PIN 12  
```  

A few things to note about **constants**...

- A **constant** is not a variable. 
- You cannot change the value of `LED_PIN`, so code like this: `LED_PIN = LED_PIN + 1`, is not valid.
- Unlike a normal statement, `#define` do not end with a semicolon.
- There are no `=` sign between `LED_PIN` and `11`.
- The names used for **constants** are usually written in all uppercase. 
  - This is not a requirement, but it is a common practice.

> Hint:
> 
> Constants are not strictly necessary in a program, but it's important to understand it as 
> you'll see it very often in tutorials and code written by others.
>  
> In the above example, `OUTPUT`, `HIGH`, and `LOW` are all **constants** that 
> are built into the Arduino software.  
