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

# Electricity and Power Basics

## Key Terminology

- Voltage
	- Measured in Volts (V)
- Current
	- Measures in Amperes (A)
	- Amperes also shortened to Amps
- Resistance
	- Measured in Ohms ()
- Power
	- Measured in Watts (W)


## Signals

A signal may be in two forms:
- Analog
- Digital

### Analog Signal

> Analog signals are continuous-time **signals that can take on** any value within a specified range. 
> 
> These signals are often **used to represent physical phenomena**, such as sound, temperature, and pressure. 
> 
> Unlike digital signals, which have distinct states that can be either 0 or 1, analog signals can be any value between two extreme values.

cepiio. (2024, May 8). _Understanding Analog Signals: A Comprehensive Guide – Exploring the World of Electronic Instruments_. Cepio. https://www.cepi.io/understanding-analog-signals-a-comprehensive-guide/

### Digital Signal

Has two discrete values:
- High
	- High is represented by a larger voltage
- Low
	- Low is represented by a small or zero voltage

If you have a circuit that is using a 1.5V battery then the high level signal would be very close to 1.5V, whereas the low level signal would be zero of very close to zero.

<iframe width="560" height="315" src="https://www.youtube.com/embed/WxJKXGugfh8?si=nB-sMXwQuVlX3zej" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

https://youtu.be/WxJKXGugfh8?si=XNywhoOlKPtwaMez

### Ground

> In electronics and electrical engineering, it is by convention we define a point in a circuit as a reference point. 
> 
> This reference point is known as ground (or GND) and carries a [voltage](https://eepower.com/textbook/vol-i-foundations-power-design/chapter-1-introduction-power/power-dc-circuits) of 0V, and a current of 0A. 
> 
> Voltage measurements are relative measurements. That is, a voltage measurement must be compared to another point in the circuit. If it is not, the measurement is meaningless.

[An Introduction to Ground: Earth Ground, Common Ground, Analog Ground, and Digital Ground - Technical Articles (allaboutcircuits.com)](https://www.allaboutcircuits.com/technical-articles/an-introduction-to-ground/)




### Floating Signal

A signal is said to be floating if it has no fixed reference voltage to work from.

If you have a floating signal then the circuit will 'randomly' select the value of the voltage.

<iframe width="560" height="315" src="https://www.youtube.com/embed/wxjerCHCEMg?si=6vpA5FGeiLjf1pu9" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

https://youtu.be/wxjerCHCEMg?si=Rz9J2xOheNo3ih2o

## Ohm's Law

Ohm’s law is the fundamental equation used in electrical engineer and is the relationship between voltage, resistance and current.

[Ohm's Law - Electronics Glossary of Terms | CircuitBread](https://www.circuitbread.com/glossary/ohms-law)

Voltage = Current * Resistance

> V = I × R

 Voltage equals the current times resistance. 
 
 This simple equation is easily re-arranged depending on what variables you have and which variable you need to solve for...

> I = V ÷ R
> 
> R = V ÷ I


https://www.circuitbread.com/tutorials/ohms-law-tutorial-with-easy-practice-problems

## Electric Power

The power transferred by an electric current is the product of its…

- voltage (the "strength" of the moving charges)
- current (the "amount" of moving charge)

[Electric Power - Summary – The Physics Hypertextbook](https://physics.info/electric-power/summary.shtml)

Power = Voltage * Current

> P = V × I

This can be reorganised to become:

> V = P ÷ I
> I = P ÷ V

When combined with Ohm's Law, we are able to work out Power even if one of the V or I are missing...

> I Missing: P = V² ÷ R
> V Missing: P = I² × R


### Easy Reference Diagram

![The Voltage, Resistance, Current and Power Interrelationship](/assets/VIRP@1x.png)

## Resistors in Series and Parallel

### Resistors in Series

![](../assets/CleanShot%202024-07-29%20at%2019.54.37@2x.png)

If you have 2 resistors in series, you simply add their resistances together.

Total R = R1 + R2 + ...

### Resistors in Parallel

![](../assets/CleanShot%202024-07-29%20at%2019.53.36@2x.png)

This is slightly harder to calculate as...

1 / Total Resistance = (1 ÷ R1) + (1 ÷ R2) + ...

If you have two resistors:

Total Resistance = (R1 × R2) ÷ (R1 + R2)


## Voltage Divider

A Voltage divider is a method of reducing a higher voltage into a smaller voltage for use in another part of a circuit. It does this by using the fact that as you pass a voltage through a resistor the voltage is dropped by a set amount.


A Voltage divider circuit looks like this:

![](../assets/CleanShot%202024-07-29%20at%2019.49.04@2x.png)



To calculate the Voltage Output we use:

Vout = Vin × R2 ÷ (R1 + R2)

<iframe width="560" height="315" src="https://www.youtube.com/embed/EQtwsWJuUPs?si=2cL69JKv1r8KMlvK" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

https://youtu.be/EQtwsWJuUPs?si=2cL69JKv1r8KMlvK


## Current Divider

A current divider takes a higher current value and divides it up across multiple paths of a circuit as defined by the resistances of those paths.

![](../assets/CleanShot%202024-07-29%20at%2019.59.52@2x.png)

The current across the two resistors (R7 and R8) in this diagram, is shown as I1 and I2.

Before we can go anywhere you need to know the total Resistance across the parallel resistor circuit.

(R1 × R2) ÷ (R1 + R2)

Ix = It x Rt / Rx

I1 = (Iin × R7) ÷ (R7 + R8)
I2 = (Iin × R8) ÷ (R7 + R8)

So if **Iin** is 1A, **R7** is 10,000Ω and **R8** is 250Ω...

I1 = 1 × 10000 ÷ (10000 + 250) = 0.976A = 976mA
I2 = 1 × 250 ÷ (10000 + 250) = 0.024A = 24mA

# Current Limiting Resistors

<iframe width="560" height="315" src="https://www.youtube.com/embed/81zNcctopBI?si=6flKcrZwtgv0Puqj" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

https://youtu.be/81zNcctopBI?si=6flKcrZwtgv0Puqj
