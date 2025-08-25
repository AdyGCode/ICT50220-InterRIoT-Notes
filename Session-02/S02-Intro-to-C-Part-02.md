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

[S02-Intro-to-C-Part-01.md](S02-Intro-to-C-Part-01.md) | [S02-Intro-to-C-Part-03.md](S02-Intro-to-C-Part-03.md)

# Variables and Types  
  
> #### Important
> 
> Before you start, make sure you've completed **Intro to C++** 
> as we'll be using the Serial prints that was covered there.  
  
In programming, variables are used to store values.  

These values can be of different types, such as integers, floats, and strings.  
  
## Defining Variables  
  
In C++, we must define the variables before we can use them. 

To illustrate, try the following example...  
  
```cpp
int foo1 = 100;  
unsigned int foo2 = 60000;  
long foo3 = 2000000000;  
float foo4 = 123.456;  
char foo5 = 'A';  
String foo6 = "Hello World";  
bool foo7 = true;  
  
void setup() {  
  // put your setup code here, to run once:
  Serial.begin(9600);
}
  
void loop() {  
  // put your main code here, to run repeatedly:
  Serial.println(foo1);
  Serial.println(foo2);
  Serial.println(foo3);
  Serial.println(foo4);
  Serial.println(foo5);
  Serial.println(foo6);
  Serial.println(foo7);
  delay(5000);
}  
```  
  
`int foo1 = 100` : 
- This defines the variable **foo1** as type `int` (integer) and a starting value of 100.  
`foo1` 
- is the name of the variable, and you can use (almost) any name you want, as long as it starts with a alphabet and does not contain spaces or special characters.  
- On most Arduinos, an `int` is a 16-bits value, and it can store a number that ranges from -32,768 to 32,767. 
- It can only store integers (whole numbers), and cannot store non-integer numbers such as **1.2** or **45.6**.  
  
`unsigned int foo2` : 
- This defines the variable **foo2** as type **unsigned int** (unsigned integer).  
- On most Arduinos, an unsigned integer is a 16-bits value, and it can store a number that ranges from 0 to 65,535.  
		- It can store numbers twice the size of `int`, but cannot store negative numbers.  
  
`long foo3` : 
- This defines a the variable **foo3** as type `long` (long integer).  
- On most Arduinos, an `int` is a 16-bits value, and it can store a number that ranges from -2,147,483,648 to 2,147,483,647.  
- There is also an unsigned version of long (`unsigned long`) that allows you to store numbers twice the size, at the cost of being unable to handle negative numbers.  
  
`float foo4` : 
- This defines the variable **foo4** as type `float` (floating point number), a number that has a decimal point.  
- A floating point number has around 6-7 decimal digits of precision.  
- That's the total number of digits, not the number to the right of the decimal point.  
- It can store a number that ranges from -3.4028235E+38 to 3.4028235E+38.  
  
`char foo5 = 'A'` : 
- This defines the variable **foo5** as type `char` (character).  
- `char` are used to store a *single character*.  
- Note that when specifying the value for the character, we use single quotes **'A'**; double quotes are used for strings.  
  
`String foo6 = "Hello World"` : 
- This defines the variable **foo6** as type `String`.  
- Strings are used to store words, sentences, or paragraphs, and when specifying the value for a String, we use double quotes **"Hello World"**.  
  
`bool foo7 = true` : 
- This defines the variable **foo6** as type `bool` (boolean).  
- Booleans have only two possible values; `true` or `false`.  
  
## Variable Scope  
  
In the above example, all of the variables are defined outside of `setup` and `loop`.  

Such variables are called **global variables**, and they can be used in any functions.  
  
Functions that are defined inside of a function are called **local variables**, and they can only be used within that function itself.  

Here's an example that illustrates the difference...  
  
```cpp
int foo1 = 100;  
  
void setup() {  
  int foo2 = 200;  
  Serial.begin(9600);
    
  // Both foo1 and foo2 can be used here  
  Serial.println(foo1);  
  Serial.println(foo2);
}  
  
void loop() {  
  Serial.println(foo1);  
  Serial.println(foo2); 
  // This line will cause an error as foo2 isn't available outside of setup.  
  delay(5000);
}  
```  
  
The above code won't work as **foo2** is defined inside of `setup`, so it cannot be used in `loop`.  

If you remove (or comment out) the `Serial.println(foo2);` in `loop`, the code will then work.

