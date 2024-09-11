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

# Session 02 Exercises & Journals 

```table-of-contents
title: # Contents
style: nestedList
minLevel: 0
maxLevel: 3
includeLinks: true
```

---


For this week's journal and consolidation learning exercises we would like you to do the following...

## Journal entry

The journal entry this week will contain images from the consolidation exercises, plus the following:

- A summary of what you have learned, including any topics you found difficult to follow.
- Any research you performed as part of the consolidation learning.
- A summary of each of the exercises and images showing the TinkerCAD circuits.

## Exercises

For each of the exercises, add a screenshot of your circuit in TinkerCAD to your Journal, plus link to the "Tinker".

### Toggled Flasher

Create a circuit that has two LEDs (You choose the colours), and two 330 Ohm resistors. It also has a pushbutton switch and a resistor configured to 'pull down' the switch input to LOW by default.

Wire up the circuit, and write the code, using an Arduino and a small breadboard so that:

- The code is NON blocking
- The first LED starts flashing by default
- When the button is pressed (and released) again the other LED will flash, and the currently flashing LED will stop
- The LEDs will flash at a rate of on for 500ms and off for 750ms

> **Hint 1:** Start by solving the different on/off periods for the on and off for ONE of the LEDs.

> **Hint 2:** Add switch detection to check if button pressed, and to toggle a value to enable the correct LED to flash.




