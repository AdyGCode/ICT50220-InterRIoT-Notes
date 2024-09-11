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

# Power and MCUs

Electronics devices consume power.

For example, the ESP32-WROVER-E and ESP-WROVER-IE have the following specifications:

| Symbol   | Parameter                    | Min  | Max   | Unit |
| -------- | ---------------------------- | ---- | ----- | ---- |
| VDD33    | Power supply voltage         | –0.3 | 3.6   | V    |
| I Output | Cumulative IO Output current | -    | 1,100 | mA   |

[esp32-wrover-e_esp32-wrover-ie_datasheet_en.pdf (espressif.com)](https://www.espressif.com/sites/default/files/documentation/esp32-wrover-e_esp32-wrover-ie_datasheet_en.pdf)

Each GPIO pin, though, cannot output the whole of the "I Output".

The output from a particular GPIO pin will be in the range ~5mA to ~40mA depending on the GPIO pin type. With a default output of ~20mA.

[esp32_datasheet_en.pdf (espressif.com)](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)

So what does that mean?

It means that the GPIO pins cannot power a device such as a motor as they do not have enough current output. We need to use some form of "driver circuit".


# Sleep Modes and Saving Power

As we know, 


[Back to Session 04...](ReadMe.md)
