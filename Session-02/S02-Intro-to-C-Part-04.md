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

[S02-Intro-to-C-Part-03.md](S02-Intro-to-C-Part-03.md) | [S02-Intro-to-C-Part-05.md](S02-Intro-to-C-Part-05.md)


# Conditions

To let the program make decisions, we can use the **if** statement.

The **if** statement lets us check if an expression is **true** or **false**, and execute code based on the result.  
Here's an example...

```cpp 
int a = 1;  
  
void setup() {  
  Serial.begin(9600);}  
  
void loop() {  
    Serial.println(a);  
    if (a == 10) {
       Serial.println("Bang!");  
    }  
    a = a + 1;  
    delay(1000);
}  
```  

`if (a == 10)` : 
- This checks if **a** is equal to **10**.
- When making a comparison, we use double equal `==` 
- Single equal `=` is used when assigning a value.  
- If the expression is true, the Arduino will run the code inside the curly brackets.

## else

We can also tell the Arduino to execute a different set of code if the expression is false...

```cpp
int a = 1;  
  
void setup() {  
  Serial.begin(9600);}  
  
void loop() {  
    Serial.println(a);  
    if (a == 10) {    
        Serial.println("Bang!");  
    } else { 
        Serial.println("Whizz...");  
    }  
    a = a + 1;  
    delay(1000);
}  
```  

## else if

We can also use **else if** to make multiple comparisons...

```cpp
int a = 1;  
  
void setup() {  
  Serial.begin(9600);
}  
  
void loop() {  
    Serial.println(a);  
    if (a == 10) {    
        Serial.println("Bang!");  
    } else if (a == 9) {
            Serial.println("Almost there.");  
    } else {    
            Serial.println("Whizz...");  
    }
    a = a + 1; 
    delay(1000);
}  
```  

## Comparison Expressions

There are multiple types of expressions that we can use...

| Expressions | Meaning                      |     |
| ----------- | ---------------------------- | --- |
| `a == b`    | a equal to b                 |     |
| `a != b`    | a not equal to b             |     |
| `a < b`     | a less than b                |     |
| `a <= b`    | a less than or equal to b    |     |
| `a > b`     | a greater than b             |     |
| `a >= b`    | a greater than or equal to b |     |

## Combining Expressions

Two or more expressions can also be evaluated together using the **&&** (AND) and **||** (OR) operators.

| Expressions          | Meaning                           |     |
| -------------------- | --------------------------------- | --- |
| `a == b && b == c`   | a equal to b **AND** b equal to c |     |
| `a == b \|\| b == c` | a equal to b **OR** b equal to c  |     |
  `||`
