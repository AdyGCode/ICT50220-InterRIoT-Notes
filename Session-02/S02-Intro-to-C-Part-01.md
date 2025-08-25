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

These notes are based on the [Arduino in Cpp](https://github.com/QuirkyCort/tutorials/tree/main/courses/100%20Arduino%20in%20Cpp) notes provided by: https://github.com/QuirkyCort/tutorials

[S02-Intro-to-C-Part-02.md](S02-Intro-to-C-Part-02.md)


## Introduction

  
Before C++, there was the C programming language.  

C was developed in 1972 by Dennis Ritchie and compared to the alternatives at the time, it provided many benefits such as portability (the same code can run on different CPU) and efficiency.  
  
C++ was developed by Bjarne Stroustrup in 1979 to add new features to C, most notably support for object oriented programming.  

As for what an "object" is, well, that's something we'll leave for much later.  
  
Today, while more modern programming languages such as Python and Javascript may lead in popularity, C and C++ remains the most common programming language when performance and control is needed.  

Most operating systems are written in C/C++, and microcontrollers are **mostly** programmed in the same.

## Setup and Loop

In the default template, you will see two special functions:
- `setup` 
- `loop`
  
When an Arduino/ESP32 or similar MCU starts up (or resets), it'll run the `setup` function **once**.  

After that, it'll run the `loop` function **repeatedly forever**.  

```cpp
void setup() {
  // put your setup code here, to run once:
}

  

void loop() {
  // put your main code here, to run repeatedly:
}
```

Right now, both of these functions are empty.  

The lines with the `//` in front of them are comments, they do nothing.  
  
This is what each component in the code means...  
  
```cpp  
void setup() {  
    // put your setup code here, to run once:
}  
```  
  
- `void`
	- The `void` in front of `setup` means that the `setup` functions does not return any values.  
- `setup()` 
	- The `( )` at the end of `setup` tells the Arduino compiler that `setup` is a function.  
- `{}`
	- The curly brackets (also call "braces") demarcates the content of the `setup` function.  
- `//` 
	- The double slashes indicates that everything after it is a comment. The compiler will ignore it.

## Examples

Open TinkerCAD and create a new circuit.

Add an Arduino to the sketch.

Next open the code and update it to read:

```cpp
void setup() {  
  // put your setup code here, to run once:  
  Serial.begin(9600);
}  
  
void loop() {  
	  // put your main code here, to run repeatedly:
	  Serial.print("Hello");  
	  delay(1000);  
	  Serial.println("World");  
	  delay(1000);
}
```


Run the simulation and check the output by clicking on the Serial Monitor.

![](../Pasted%20image%2020250725164249.png)

### Key Parts of the Code

Here is what the code mean...  
  
`Serial.begin(9600);`
- This initializes the serial port at a baud rate of 9600 (bits per second). 
- When the Arduino is plugged into the computer, it provides a serial connection that you can use to communicate with the Arduino. 
- We may also use it to send messages to the computer.  
- Notice the semicolon at the end of the line? Every statement in C++ must end with a `;`, it indicates to the compiler that the statement has ended.

`Serial.print("Hello");`
- This sends the message "Hello" to the computer. 
- Note that the double quotes `"` `"` indicate that "`Hello`" is a string. 
- Strings are used to represents words, sentences, and paragraphs.  
  
`delay(1000);`
- This creates a 1000ms (1 second) delay. 
- Basically, the Arduino will do nothing for 1 second before moving on to the next instruction.
- **Important:** `delay()` is a **BLOCKING** function.
  
`Serial.println("World");`
- Notice that this is a little different from the previous `Serial.print`? 
- When using `Serial.println`, the Arduino will add a newline at the end.
  - That means that the next print will start on the next line.

