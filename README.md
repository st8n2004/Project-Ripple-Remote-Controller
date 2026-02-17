# Project Ripple Remote Controller

This repository contains the files required to reproduce the remote controller subsystem for Project Ripple.

## Contents

- Arduino firmware for ESP32 LoRa V3 controller
- Electrical wiring diagrams
- Hardware documentation

## Hardware Components

- ESP32 LoRa V3 Development Board (915 MHz)
- 10k Linear Slider Potentiometers (2)
- 915 MHz Antenna
- Battery Power Supply

## Connections
| Signal              | ESP32 Pin     | Connected Component         | Voltage Range |
| ------------------- | ------------- | --------------------------- | ------------- |
| Steering Input      | GPIO2         | 10 kΩ Potentiometer (wiper) | 0–3.3 V       |
| Throttle Input      | GPIO3         | 10 kΩ Potentiometer (wiper) | 0–3.3 V       |
| Potentiometer Power | 3V3           | Both Potentiometers         | 3.3 V         |
| Ground              | GND           | Both Potentiometers         | 0 V           |
| RF Communication    | SMA Connector | 915 MHz Antenna             | RF Signal     |


## Software

Firmware developed using Arduino IDE in C++.

## Communication

LoRa transmission at 915 MHz for long-range control (>1 mile).

## Authors

Project Ripple Team
University of Kentucky
