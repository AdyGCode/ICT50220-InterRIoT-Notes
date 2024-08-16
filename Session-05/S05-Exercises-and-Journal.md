# Session 05 Exercises & Journals 

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
- A summary of each of the exercises.

# Version Controlling Your Code

Make sure you have followed the steps for Session 03 Exercises and have your code version controlled.

## Exercises

For each of the exercises, as required do the following:

- Design a circuit for the exercise
- Wire the circuit on the breadboard with the components needed
- Take a photo of the wiring
- Design the code to drive the circuit
- Test the code
- Commit the code to your repository and push to GitHub 

For each of the exercises below, create a markdown document in the **Session-05** folder that is named the same as the headings below, replacing any non-Alpha-Numeric characters with dashes (`-`).

### Sleepy Flasher

Markdown Document: `Sleepy-Flasher.md`

Create a circuit that has:
- 1 x green LED
- 1 x 220 Ohm resistor
- 1 x pushbutton switch
- 1 x 10k Ohm resistor

The circuit will:
- connect the LED to GPIO 2 via the 220 Ohm resistor, and to ground.
- connect one side of the the pushbutton to ground via the 10K resistor, and to the GPIO 33
- connect the diagonally opposite side of the pushbutton to the 3V3 rail

Write the code to:
- create a **non-blocking** LED flasher that flashes the LED once every 100 milli seconds.
  *Make sure you test this works before continuing.*
- Put the ESP-32 into sleep mode
- Wake the ESP32 when the button is pressed
- Whilst the button is held down, the ESP-32 will flash the LED
- When the button is released the ESP32 will go to sleep
  *Test the code works and your ESP-32 does what is expected.*


### Sleepy Toggle

In this problem we want to solve the following problem:

Create an IoT device that is based on the ESP-32. The device will go to sleep and be woken up every 5 minutes to flash a RED led for 200ms. It will also wake up when a button is pressed and flash a GREEN led for 200ms.

For this you will need:

| Qty | Component         | Notes |
| --- | ----------------- | ----- |
| 1   | LED               | green |
| 1   | LED               | red   |
| 2   | 220 Ohm resistors |       |
| 1   | 10k Ohm resistor  |       |
| 1   | Pushbutton switch |       |
|     | Jumper cables     |       |

Remember that jumper cables have colour to aid identification.
- RED is to be used for 3V3
- BLACK for GROUND
Other colours are used to aid tracing of the circuits as needed.

### Sleepy MQTT

In this problem we are aiming to have an IoT Device wake from sleep every 5 minutes and send a value (the boot count) to an Adafruit feed.

Each wake up will increment the boot count.

This combines parts of Session 4 and Session 5.

