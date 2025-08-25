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

# Session 03 Review Exercises 

```table-of-contents
title: # Contents
style: nestedList
minLevel: 0
maxLevel: 3
includeLinks: true
```

---

# Getting Ready

If you have not done so, follow the instructions in [S01 Notes And Review Exercises](../Session-01/S01-Notes-And-Review-Exercises.md) to set up a Markdown based Notes Repository.

> ##### Aside: 
> 
> _Adrian and other lecturers use Obsidian as a markdown editor and note organisation tool every day. In fact these notes are created using Obsidian._


Once you have completed the steps in the  [S01 Notes And Review Exercises](../Session-01/S01-Notes-And-Review-Exercises.md), open the Windows Terminal. 

> **Note:**
> These steps are for the Windows PCs in Room 3-06.
> 
> `YOUR_USER_NAME` must be replaced by the username you use for logging into the systems in 3-06, and `xxx` must be replaced by your initials.


#### Windows Command Prompt time

This is one of the few times we will use the Windows command prompt. This is because we want to make a *Windows Junction Link* to a folder called Arduino so we do not have to copy code into the repos folder every time, nor have to remember where the Arduino code is kept.

Open the Terminal application, and then use the `∨`  to show the shell options. Select the "Command Prompt" option.

Once the (DOS) Command prompt is open you will use the following to create a "Junction" link between a new access point a new folder called "Arduino".

```shell
cd %userProfile%
mkdir Source\Repos\Arduino
mklink /J Arduino Source\Repos\Arduino
```

The first command moves you into your User's Home/Profile folder.

The second creates a `Arduino` folder inside the `Source/Repos` folder.

If any of the parent folders do not exist, then they are created on the way to the Arduino folder being made.

You may now use the command `exit` to close this CLI and have the Bash terminal come to the foreground.

#### Back to BASH!

Now open the BASH terminal and use the following:

```shell
cd /c/Users/YOUR_USER_NAME/Documents/Arduino
```

## Exercises

The following exercises are going to be created in TinkerCAD and then using the Arduino IDE.

For each of the exercises, add a screenshot of your circuit in TinkerCAD to your Notes and Exercises repository, plus a hyperlink to the "Tinker".

Also, we will be creating and working with physical electronics devices, and you will be required to create Arduino (ESP32/Arduino Uno) projects that are contained in the repository above.

For each of the exercises below, create a markdown document in the **Session-03** folder that is named the same as the headings below, replacing any non-Alpha-Numeric characters with dashes (`-`).

### Exercise 1: Bouncy Button

Markdown Document: `Bouncy-Button.md`

Follow the tutorial [Arduino: De-Bounce a Button with micros() or millis() - Bald Engineer](https://www.baldengineer.com/arduino-de-bounce-a-button-with-micros.html) to learn how to de-bounce a button.

Create the circuit and code in TinkerCAD. 

Run the simulation to ensure it works as expected.

Take a screenshot of the circuit. 

Save the screenshot with a suitable name so it is easily identified by the lecturer and yourself.

Insert the screenshot into your Markdown document along with any summary details you may find useful, including a APA 6/APA 7 Bibliographic entry for the references, and the article used.

> **Remember** use MyBib to create your Bibliographic Entries.


### Exercise 2: Toggled Flasher


Create a circuit that has two LEDs (You choose the colours), and two 330 Ohm resistors. It also has a pushbutton switch and a resistor configured to 'pull down' the switch input to LOW by default.

Wire up the circuit, and write the code, using an Arduino and a small breadboard so that:

- The code is NON blocking
- The first LED starts flashing by default
- When the button is pressed (and released) again the other LED will flash, and the currently flashing LED will stop
- The LEDs will flash at a rate of on for 500ms and off for 750ms

> **Hint 1:** Start by solving the different on/off periods for the on and off for ONE of the LEDs.

> **Hint 2:** Add switch detection to check if button pressed, and to toggle a value to enable the correct LED to flash.


Take a screenshot of the circuit. 

Save the screenshot with a suitable name so it is easily identified by the lecturer and yourself.

Insert the screenshot into your Markdown document along with any summary details you may find useful, including a APA 6/APA 7 Bibliographic entry for the references, and the article used.


### Exercise 3: Detect Long and Short Button Press

Follow the tutorial [Detect short and long button press using millis - Bald Engineer](https://www.baldengineer.com/detect-short-long-button-press.html) using TinkerCAD.


Create the circuit and code in TinkerCAD. Run the simulation to ensure it works as expected.

Take a screenshot of the circuit. 

Save the screenshot with a suitable name so it is easily identified by the lecturer and yourself.

Insert the screenshot into your Markdown document along with any summary details you may find useful, including a APA 6/APA 7 Bibliographic entry for the references, and the article used.


### Exercise 4: Multitasking Arduino

For this exercise we require you to complete the following tutorial. 

- ed. (2019, January 7). _How To Do Multitasking With Arduino - The Robotics Back-End_. The Robotics Back-End. https://roboticsbackend.com/how-to-do-multitasking-with-arduino/

‌

You will need to:
1) Create the TinkerCAD circuit
2) Add the Code
3) Add Comments to the given code
4) Test the simulation

### Exercise 5: Multitasking Arduino v2

For this exercise we want you to duplicate the previous circuit, then complete the following task:

- Update the code to put each task into a function.
- Ensure you are passing the required values into the functions.
- Only use global variables in the start and loop functions.

You may make use of static variables in functions if that makes the coding simpler to implement.


### Exercise 6: Multitasking Arduino v3

This time you are to create the circuit using a physical Arduino and components.

After wiring up the circuit, ask your workshop coordinator/assessor/lecturer to check the wiring before connecting up and coding.

Use the code from the second version of this Multitasking exercise.


### Exercise 7: Arduino Interrupts

Complete the following tutorial on Arduino Interrupts

- ed. (2019, May 25). _Arduino Interrupts Tutorial - The Robotics Back-End_. The Robotics Back-End. https://roboticsbackend.com/arduino-interrupts/

‌
### Exercise 8: Arduino Protothreads

Complete the following tutorial

- ed. (2019, June 10). _Arduino Protothreads [Tutorial] - The Robotics Back-End_. The Robotics Back-End. https://roboticsbackend.com/arduino-protothreads-tutorial/

‌