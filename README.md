# Motor Control & Vibration Monitoring System

## Overview
This project implements a real-time motor control and vibration monitoring system using embedded hardware integrated with MATLAB for signal analysis. The system ensures safe motor operation by detecting abnormal vibrations and automatically shutting down the motor.

## Features
- Push-button based DC motor ON/OFF control
- Real-time vibration detection using SW-420 sensor
- Automatic motor shutdown on excessive vibration
- LED indicators for system status (normal/fault)
- LCD display for real-time monitoring
- Serial communication with MATLAB for data analysis

## Components Used
- NodeMCU (ESP8266)
- L298N Motor Driver
- SW-420 Vibration Sensor
- 16x2 LCD (I2C)
- Push Buttons & LEDs
- MATLAB (Serial Communication & FFT Analysis)

## Working Principle
The vibration sensor continuously monitors the motor condition. When vibration exceeds a threshold, the ESP8266 detects it and immediately shuts down the motor. Data is transmitted via serial communication to MATLAB, where it is analyzed and visualized in real time.

## Functionality
- Controls motor using push-button input
- Monitors vibration in real time
- Detects abnormal vibration conditions
- Stops motor automatically during faults
- Sends live data to MATLAB for visualization
- Performs FFT-based frequency analysis

## MATLAB Integration
- Real-time time-domain signal plotting
- FFT analysis using rolling buffer
- Identification of vibration frequency components
- Visualization of normal vs faulty conditions

## System Behavior
- Normal Condition:
  - Motor ON
  - Green LED ON
  - Stable signal in MATLAB

- Fault Condition:
  - Motor OFF automatically
  - Red LED ON
  - Peaks in signal and FFT graph

## My Contribution
- Designed and implemented complete embedded system
- Integrated motor driver, sensor, and display modules
- Developed Arduino code for control and monitoring
- Implemented MATLAB scripts for real-time plotting and FFT
- Tested and validated system performance

## Applications
- Industrial motor protection systems
- Predictive maintenance
- Fault detection in rotating machinery
- Condition monitoring systems

## Code
- Arduino code: `code/arduino.ino`
- MATLAB scripts: `matlab/analysis.m`

## Output
The system successfully detects abnormal vibration conditions and shuts down the motor in real time. MATLAB visualization clearly distinguishes between normal and faulty states using time-domain and frequency-domain analysis.

## MATLAB Output (Time Domain)
![Time Domain](images/time-domain.png)

## MATLAB Output (FFT)
![FFT](images/fft.png)

## Circuit Diagram
![Circuit](images/circuit.png)

## Hardware Setup
![Setup](images/setup.png)
