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

[S02-Intro-to-C-Part-02.md](S02-Intro-to-C-Part-02.md) | [S02-Intro-to-C-Part-04.md](S02-Intro-to-C-Part-04.md)

# Math and Type Conversion  
  
Try the following...  
  
```cpp
int a = 100;  
int b = 1;  
  
void setup() {  
  // put your setup code here, to run once:  
  Serial.begin(9600);
}  
  
void loop() {  
  // put your main code here, to run repeatedly: 
   Serial.println(a + b);  
  b = b + 1;  
  delay(1000);
}  
```  
  
We can perform some simple math operations on variables using...  
  
* `+` : Plus  
* `-` : Minus  
* `*` : Multiply  
* `/` : Divide  
  
## Type Conversion  
  
You cannot add a `String` and a number (e.g. `int`, `float`); adding a word and a number simply doesn't make sense.  

But you can add a String and a String together like this...  
  
```cpp  
String a = "Hello ";  
String b = "World";  
Serial.println(a + b);  
```  
  
This will cause the Arduino to print "Hello World" on the serial monitor.  
  
### Number to String  
  
To convert a number (e.g. `int`, `float`) into a `String`, you can do...  
  
```cpp  
String a = "The result is:";  
int b = 42;  
a = a + String(b);  
Serial.println(a);  
```  
  
### String to Number  
  
If you need to convert a String into a number, you can do so like this...  
  
```cpp  
String a = "100";  
Serial.println(a.toInt() + 1);  
```  
  
This will convert the String variable **a** into an integer.  

You can also use `.toFloat()` to convert it into a float.  
  
