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

# Resistor Standard Values

Resistors do not come in an infinite number of values, it is simply impractical to do so.

Instead, they have a number of standard values that are available, along with standardised "variances".

## Calculating Resistor Value Range

The tolerance value (a value in percent %) indicates the range that is acceptable for the type of resistor.

A reistor with a tolerance of 5% will have a range that is -5% to +5% of teh nominated value.

For example:

| Resistor Value | Tolerance | Variance | MNin Resistance | Max Resistance |
|----------------|-----------|----------|-----------------|----------------|
| 1000Ω           | 10%       | 100Ω      | 900Ω             | 1100Ω          |

## Resistor Value Tables

Below are the standard resistor value tables for 1%, 2%, 5% and 10% variances.

Many thanks to https://www.rfcafe.com/references/electrical/resistor-values.htm for the information.

### 1% Standard Values (EIA E96)

Decade multiples are available from 10.0 Ω through 1.00 MΩ

(also 1.10 MΩ, 1.20 MΩ, 1.30 MΩ, 1.50 MΩ, 1.60 MΩ, 1.80 MΩ, 2.00 MΩ and 2.20 MΩ)

|      |      |      |      |      |      |      |      |      |      |      |      |
|------|------|------|------|------|------|------|------|------|------|------|------|
| 10.0 | 10.2 | 10.5 | 10.7 | 11.0 | 11.3 | 11.5 | 11.8 | 12.1 | 12.4 | 12.7 | 13.0 |
| 13.3 | 13.7 | 14.0 | 14.3 | 14.7 | 15.0 | 15.4 | 15.8 | 16.2 | 16.5 | 16.9 | 17.4 |
| 17.8 | 18.2 | 18.7 | 19.1 | 19.6 | 20.0 | 20.5 | 21.0 | 21.5 | 22.1 | 22.6 | 23.2 |
| 23.7 | 24.3 | 24.9 | 25.5 | 26.1 | 26.7 | 27.4 | 28.0 | 28.7 | 29.4 | 30.1 | 30.9 |
| 31.6 | 32.4 | 33.2 | 34.0 | 34.8 | 35.7 | 36.5 | 37.4 | 38.3 | 39.2 | 40.2 | 41.2 |
| 42.2 | 43.2 | 44.2 | 45.3 | 46.4 | 47.5 | 48.7 | 49.9 | 51.1 | 52.3 | 53.6 | 54.9 |
| 56.2 | 57.6 | 59.0 | 60.4 | 61.9 | 63.4 | 64.9 | 66.5 | 68.1 | 69.8 | 71.5 | 73.2 |
| 75.0 | 76.8 | 78.7 | 80.6 | 82.5 | 84.5 | 86.6 | 88.7 | 90.9 | 93.1 | 95.3 | 97.6 |

### 2% Standard Values (EIA E48)

Decade multiples are available from 10 Ω through 22 MΩ

E.g. To get a 3830 Ohm resistor multiply 38.3 by 10.

|      |      |      |      |      |      |      |      |      |      |      |      |
|------|------|------|------|------|------|------|------|------|------|------|------|
| 10.0 | 10.5 | 11.0 | 11.5 | 12.1 | 12.7 | 13.3 | 14.0 | 14.7 | 15.4 | 16.2 | 16.9 |
| 17.8 | 18.7 | 19.6 | 20.5 | 21.5 | 22.6 | 23.7 | 24.9 | 26.1 | 27.4 | 28.7 | 30.1 |
| 31.6 | 33.2 | 34.8 | 36.5 | 38.3 | 40.2 | 42.2 | 44.2 | 46.4 | 48.7 | 51.1 | 53.6 |
| 56.2 | 59.0 | 61.9 | 64.9 | 68.1 | 71.5 | 75.0 | 78.7 | 82.5 | 86.6 | 90.9 | 95.3 |

### 5% Standard Values (EIA E24)

Decade multiples are available from 10 Ω through 22 MΩ

|    |    |    |    |    |    |    |    |    |    |    |    |
|----|----|----|----|----|----|----|----|----|----|----|----|
| 10 | 11 | 12 | 13 | 15 | 16 | 18 | 20 | 22 | 24 | 27 | 30 |
| 33 | 36 | 39 | 43 | 47 | 51 | 56 | 62 | 68 | 75 | 82 | 91 |

### 10% Standard Values (EIA E12)

Decade multiples are available from 10 Ω through 1 MΩ

|    |    |    |    |    |    |    |    |    |    |    |    |
|----|----|----|----|----|----|----|----|----|----|----|----|
| 10 | 12 | 15 | 18 | 22 | 27 | 33 | 39 | 47 | 56 | 68 | 82 |

## References:

For more details see the following articles:

- Storr, W. (2024, March 19). Standard Resistor Values - Electronics Tutorials. Basic Electronics
  Tutorials. https://www.electronics-tutorials.ws/resources/standard-resistor-values.html
- Kirt. (2025). Standard Resistor Values. Rfcafe.com. https://www.rfcafe.com/references/electrical/resistor-values.htm
- Keim, R. (2025). Resistor Values. Eepower.com;
  eepower.com. https://eepower.com/resistor-guide/resistor-standards-and-codes/resistor-values/#
- Standard Resistor Values (± ±5%). (n.d.). https://ch00ftech.com/wp-content/uploads/2012/05/resistorsandcaps.pdf
- Resistor Values E6 E12 E24 E48 E96 E192. (2025).
  Logwell.com. https://www.logwell.com/tech/components/resistor_values.html
- Muhammad Sufyan. (2025, April 9). Resistor Chart: Comprehensive Guide to Resistor Values, E-Series, and Color Codes.
  Wevolver. https://www.wevolver.com/article/resistor-chart-comprehensive-guide-to-resistor-values-e-series-and-color-codes