
# Energy-Meter

This project is an industrial embedded project to test and monitor three-phase networks and devices.

## Features
In this case, we are only taling about the embedded-software features:

- Calculating all important electrical parameters
- Analysing transient and steady-state 
- Advanced signal regeneration (for calc etc.) 
- Interfaces to the world


## Getting started

Three important parameter come from the stream: 
- measured current
- measured voltage
- time

In this case, the "sample.csv" contains the necessary values, wich you can test using "sample.c".

### How does the "sample.c" work?
    1. open sample.csv file
    2. count the records
    3. make three vectors
    4. upload the vectors
    5. your section: do something with the vectros

### What is in the sample.csv file?

There are simulated values from an LTSpice simulation. The sampling period is 100ms.

![App Screenshot](https://vargalaszlo.com/images/out/github-energy-meter-sample-csv.png)
