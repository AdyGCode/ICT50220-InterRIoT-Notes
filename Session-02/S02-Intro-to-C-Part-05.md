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

[S02-Intro-to-C-Part-04.md](S02-Intro-to-C-Part-04.md) | [S02-Intro-to-C-Part-06.md](S02-Intro-to-C-Part-06.md)



# Loops  
  
Loops allows us to repeat a section of code multiple times.  
There are two main types of loops; the `for` loop and the `while` loop.  
  
## for Loops  
  
This is an example of the `for` loop...  
  
```cpp 
void setup() {  
    Serial.begin(9600);
}  
  
void loop() {  
    for (int a=0; a<10; a++) {    
        Serial.println(a);  
    }  
        delay(1000);
}  
```  
  
Each `for` loop contains 3 expressions...  

#### Initialise
- `int a=0`:
- This defines a variable `a` and set it to the value `0** at the start of the `for` loop.  
  
#### Test
- `a<10`:
- This checks if the variable `a` is less than `10`.  
- If it is true, the code in the curly brackets will run.  
- If it is false, the `for` loop will end.  

#### Update
- `a++` : 
- This increments the variable `a` by one each time after running the code in the curly brackets.  
  
## while Loops  
  
This is an example of the `while` loop...  
  
```cpp  
void setup() {  
    Serial.begin(9600);
}  
  
void loop() {  
    int a = 1;  
    while (a < 5) {    
        Serial.println(a);    
        delay(200);    
        a++;  
    }  
    delay(2000);
}  
```  

The while loop also contains the three parts, Initialise, Test and Update.

#### Initliase

- `int a = 1;` 
- Set the value of the variable `a` to `1`.

#### Test
- **while (a &lt; 5)**
- This `while` loop will keep repeating the code inside the curly brackets as long as **a** is less than **5**.  

#### Update
- `a++;`
- Increments a by 1.
- If you do NOT update the control variable then you have an infinite loop.
  
## break and continue  
  
There are two special commands that can only be used inside a `for` or `while` loop:

- `break` and 
- `continue`  
  
### break  
  
The `break` commands orders the loop to end immediately.  

Here's an example...  
  
```cpp 
void setup() {  
    Serial.begin(9600);
}  
  
void loop() {  
    for (int a=0; a<10; a++) {
        Serial.println(a);
        if (a == 5) {
              break;    
          }  
    }  
    delay(1000);
}  
```  
  
In the above code, the `for` loops ends as soon as **a** is equal to **5**.  


  
### continue  
  
The `continue` commands orders the loop to immediately continue with the next iteration, skipping the code below it.  

Here's an example...  
  
```cpp
void setup() {  
    Serial.begin(9600);
}  
  
void loop() {  
    for (int a=0; a<10; a++) {    
        if (a == 5) {
              continue;    
        }    
        Serial.println(a);  
    }  
    delay(1000);
}  
```  
  
In the above code, the `for` loops skips the `Serial.println` if **a** is equal to **5**.  
  
