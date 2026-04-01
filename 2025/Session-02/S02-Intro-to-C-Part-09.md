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


[S02-Intro-to-C-Part-08.md](S02-Intro-to-C-Part-08.md) | [S02-Intro-to-C-Part-10.md](S02-Intro-to-C-Part-10.md)

# References  
  
While going through this section of the course, you have encountered built-in functions such as **delay** and `Serial.println`.  
These are just a few of the many built-in functions available in the Arduino platform.  
As well, we have only touched on some of the basic features in C++, and there are much more to the C++ programming language that we have not covered.  
  
## Arduino  
  
Even the most experienced programmer cannot remember all details of the Arduino built-in functions, so it's important for us to learn to refer to the Arduino documentations. Open the following link in a new tab, and refer to it often when programming.  
  
[Arduino Language Reference](https://www.arduino.cc/reference/en/)  
  
## C++  
  
For the C++ programming language, you can use the following tutorials to learn more  
  
[learn-c.org](https://www.learn-c.org/) This is actually a tutorial for C, not C++, but nearly everything in C applies to C++ as well.  
It's a relatively easy to follow tutorial with an interactive tool that lets you test your code in the browser.  
Note that the **printf** statements in the tutorials needs to be replaced with `Serial.print` if you are using an Arduino.  
  
[Learn C++](https://www.learncpp.com/) This is a much longer tutorial for C++.  
The tutorial expects you to install compilers and IDE on you computer to try the examples, but you can also use a free online compiler like [onlinegdb](https://www.onlinegdb.com/online_c++_compiler) instead.