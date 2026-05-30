# Display of Incremental Rotary Encoder Output on GUI Using PIC 16-bit Microcontroller

An embedded systems and human-machine interface (HMI) project developed during the *Visiting Student Programme at ARIES (VSPA)* (Jan 2026). 

## 🚀 Project Overview
This project focuses on the real-time acquisition, processing, and visualization of angular position and direction data from an industrial-grade incremental optical rotary encoder. 

### Key Features:
* *Dual-Microcontroller Architecture:* Uses a modular setup where one MCU handles high-frequency Quadrature Encoder Interface (QEI) processing and a secondary MCU handles data communication via SPI.
* *Hardware Decoding:* Offloads pulse-counting and direction detection to the PIC's internal QEI peripheral to reduce CPU overhead.
* *Real-Time HMI:* A lightweight Python GUI built with Tkinter and PySerial displaying incoming telemetry at 9600 baud.
* *Actuator Simulation:* Explores closed-loop principles via simulated Unipolar and Bipolar stepper motor driver stages (ULN2003A & L293D).

---

## 🛠️ System Architecture & Data Flow
1. *Sensing:* Incremental Optical Encoder generates Phase A and Phase B quadrature signals (90° phase-shifted).
2. *Embedded Processing:* PIC 16-bit MCU decodes direction (CW/CCW) and tracks pulse metrics via hardware QEI blocks.
3. *Transmission:* Data is encapsulated into serial data frames (COUNT: <value>) and pushed across UART via a MAX232 transceiver.
4. *Visualization:* Python desktop app parses incoming buffer frames non-blocking and dynamically updates the visual interface.

---

## 💻 Repository Contents

### 1. Embedded Firmware (/firmware)
* PIC C code configuring configuration bits for high-speed crystal execution (10 MHz).
* Peripheral register setup for QEI counting modes ($\times 1, \times 2, \times 4$) and data transfer initialization.
* Low-level step excitation patterns for stepper validation logic.

### 2. Python GUI Client (/gui)
The tracking application is written in Python utilizing event-driven callbacks:
```python
import serial
import tkinter as tk

# Automated non-blocking GUI updates every 50ms
def read_serial():
    if ser.in_waiting:
        line = ser.readline().decode(errors="ignore").strip()
        if line.startswith("COUNT:"):
            value = line.split(":")[1]
            label.config(text=f"Count: {value}")
    root.after(50, read_serial)
```
## 🎓 Acknowledgements

[span_0](start_span)I would like to express my sincere gratitude to Mr. Shobhit Yadava, Aryabhatta Research Institute of Observational Sciences (ARIES), for giving me the opportunity to carry out this short-term project under the Visiting Student Programme at ARIES (VSPA)[span_0](end_span). [span_1](start_span)I am deeply thankful for his constant guidance, encouragement, and insightful technical discussions, which were crucial in shaping my understanding throughout the course of this work[span_1](end_span).

[span_2](start_span)I sincerely thank the faculty members of the Department of Electronics and Communication Engineering, Govind Ballabh Pant Institute of Engineering and Technology, Pauri, for their academic support and encouragement throughout my undergraduate studies[span_2](end_span). 

[span_3](start_span)Finally, I express my heartfelt gratitude to my family and friends for their constant support, motivation, and understanding during this period[span_3](end_span).
