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


### Digital Signal

Has two discrete values:
- High
	- High is represented by a larger voltage
- Low
	- Low is represented by a small or zero voltage

If you have a circuit that is using a 1.5V battery then the high level signal would be very close to 1.5V, whereas the low level signal would be zero of very close to zero.

### Ground

> In electronics and electrical engineering, it is by convention we define a point in a circuit as a reference point. 
> 
> This reference point is known as ground (or GND) and carries a [voltage](https://eepower.com/textbook/vol-i-foundations-power-design/chapter-1-introduction-power/power-dc-circuits) of 0V. 
> 
> Voltage measurements are relative measurements. That is, a voltage measurement must be compared to another point in the circuit. If it is not, the measurement is meaningless.

[An Introduction to Ground: Earth Ground, Common Ground, Analog Ground, and Digital Ground - Technical Articles (allaboutcircuits.com)](https://www.allaboutcircuits.com/technical-articles/an-introduction-to-ground/)




### Floating Signal

A signal is said to be floating if it has no fixed reference voltage to work from.

If you have a floating signal then the circuit will 'randomly' select the value of the voltage.

## Ohm's Law

Ohm’s law is the fundamental equation used in electrical engineer and is the relationship between voltage, resistance and current.

[Ohm's Law - Electronics Glossary of Terms | CircuitBread](https://www.circuitbread.com/glossary/ohms-law)

Voltage = Current * Resistance

> V = I × R

 Voltage equals the current times resistance. 
 
 This simple equation is easily re-arranged depending on what variables you have and which variable you need to solve for...

> I = V ÷ R
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


## Resistors in Series and Parallel

### Resistors in Series

If you have 2 resistors in series, you simply add their resistances together.

Total R = R1 + R2 + ...

### Resistors in Parallel

This is slightly harder to calculate as...

1 / Total Resistance = (1 ÷ R1) + (1 ÷ R2) + ...

If you have two resistors:

Total Resistance = (R1 × R2) ÷ (R1 + R2)


## Voltage Divider

A Voltage divider is a method of providing a smaller voltage to another part of a circuit. It does this by using the fact that as you pass through a resistor the voltage is dropped by a set amount.

A Voltage divider ciurcuit looks like this:


## Current Divider




