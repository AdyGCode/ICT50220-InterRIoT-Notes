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

[S02-Intro-to-C-Part-05.md](S02-Intro-to-C-Part-05.md) | [S02-Intro-to-C-Part-07.md](S02-Intro-to-C-Part-07.md)


# Functions  
  
Functions are like recipes, they store your instructions and allow us to reuse them again and again.  
Here's an example of how functions are created and used in C++...  
  
```cpp 
float mean_of_two_numbers(int a, int b) {  
  float c = (a + b) / 2.0;  
  return c;
}  
  
void setup() {  
  Serial.begin(9600);
}  
  
void loop() {  
  float result = mean_of_two_numbers(2, 3);  
  Serial.println(result);  
  delay(1000);
}  
```  
  
`int mean_of_two_numbers(int a, int b)`
- This defines **mean_of_two_numbers** as a function that returns a `float` value.
- It takes two parameters; **a** and **b**, both of which are `int` types.  
- The code inside the curly brackets is the content (or body) of this function:
  - they will run whenever we call the function.  
  
`float result = mean_of_two_numbers(2, 3)`
- In this line, we call the function **mean_of_two_numbers**.
- We supply it with **2** for the first parameter and **3** for the second.  
- The value that the **mean_of_two_numbers** function returns will be stored in the **result** variable.  
  
`float c = (a + b) / 2.0`
- Here we add **a** and **b** together, then divide it by **2.0**.
- Note that we are using **2.0** and not **2**. 
- If we had used **2**, the Arduino will perform an integer calculation (you can try it and see what happens).  
  
`return c`
- This ends the **mean_of_two_numbers** function, and causes it to return the value of the variable **c**.
  
## Return Types and void  
  
You can create functions that returns any types of values (e.g. int, float, String).  
If your function does not need to return any value, you should define it as type **void** like this...  
  
```cpp 
void prints_a_and_b(int a, int b) {  
  Serial.println(a);  
  Serial.println(b);
}  
  
void setup() {  
  Serial.begin(9600);}  
  
void loop() {  
  prints_a_and_b(2, 3);  
  delay(1000);
}  
```  
  
## No Parameters  
  
If your function does not require any parameters, you should use an empty **()** like this...  
  
```cpp 
void prints_nothing() {  
  Serial.println("nothing");
}  
  
void setup() {  
  Serial.begin(9600);
}  
  
void loop() {  
  prints_nothing();  
  delay(1000);
}  
```  

> Note:
> 
> Functions are not strictly necessary in a program, but they help reduce code repetition and improve the neatness of your code.
> 
> This becomes important as your code gets longer and more complicated.  
>  
> We recommend that you create functions that hide any form of code that may be harder for other
> developers to read.
>  
> So a function call such as `ledOn(LED_RED_1)` makes sense as against `digitalWrite(13, LOW)`.

