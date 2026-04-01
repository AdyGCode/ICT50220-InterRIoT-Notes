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

[S02-Intro-to-C-Part-07.md](S02-Intro-to-C-Part-07.md) | [S02-Intro-to-C-Part-09.md](S02-Intro-to-C-Part-09.md)

# The Breadboard

A breadboard is the tinkerer's go to as it allows you to set upa temporary circuit to test your idea before constructing
the circuit on a more permanent circuit board of some form.

![](../../assets/breadboard.jpg)

It is important to make sure you note how a breadboard's holes connect.

## Dupont wires

These are wires with pins or sockets at the end.

They are just a wire, to allow you to connect components on the Breadboard.

# The Arduino

![](../../assets/arduinoParts.jpg)

| No. | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
|-----|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1   | Barrel plug for powering the Arduino. If you supply power through here, the supply voltage needs to be between 7V to 12V.                                                                                                                                                                                                                                                                                                                                                                                |
| 2   | USB socket. Use this to connect the Arduino to the computer. You can also supply power to the Arduino through here (5V only).                                                                                                                                                                                                                                                                                                                                                                            |
| 3   | Reset button. Press this to reset the Arduino; it'll run **setup** again before running **loop**.                                                                                                                                                                                                                                                                                                                                                                                                        |
| 4   | These are the GPIO pins 2 to 13. <br> Pins 0 and 1 are also GPIO pins, but they are normally used for Serial. <br> Pins with a tilde **~** next to them can be used as PWM outputs (...using analogWrite)                                                                                                                                                                                                                                                                                                |
| 5   | These 6 pins are capable of analog inputs. This means that they can read a voltage from 0V to 5V. They can also be used as normal GPIO pins.                                                                                                                                                                                                                                                                                                                                                             |
| 6   | **Vin** You can supply power to the Arduino through this pin (7V to 12V). If powered through other means, this pin will be at the same voltage as the power supply. <br> **5V** This pin provides 5V; useful for powering external components. <br> **3V3** This pin provides 3.3V; some external components will need to be powered by this. <br> **GND** This is the Ground pin. It's like the negative pole on a battery. There is one more Ground pin on the other side of the board next to pin 13. |
| 7   | These are the TX, RX, and L LEDs. The TX and RX LEDs will light up when the Arduino is transmitting or receiving data over Serial. The L LED is connected to pin 13.                                                                                                                                                                                                                                                                                                                                     |


# The ESP32

> TODO: Diagram and key to be created and added here ....
 
