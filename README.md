Project Overview

This project is a heterogeneous embedded-system platform for developing and evaluating autonomous sensing, image processing, and real-time control.

The system combines:

STM32F103 microcontroller for low-level real-time sensing and actuator control

Zynq-7000 SoC for higher-level software and FPGA hardware acceleration

ARM Cortex-A9 for software control and system coordination

FPGA programmable logic for parallel computation and image-processing acceleration

The project is being developed incrementally. The current goal is not yet to demonstrate a fully autonomous vehicle, but to build and validate the hardware/software architecture required for future autonomous operation.

The system will eventually be used to measure performance such as:

Sensor-to-control reaction time

Processing latency

CPU tick counts

PWM response time

Pure C execution time

ARM NEON/SIMD execution time

FPGA hardware-acceleration execution time

1. Project diagram v1
   <img width="1220" height="1081" alt="image" src="https://github.com/user-attachments/assets/7d944adb-b70b-46f3-8ceb-3bbc3ac64c67" />

3. Project diagram v2
```text
                    AUTONOMOUS EXPLORER CAR
                              │
             ┌────────────────┴────────────────┐
             │                                 │
             ▼                                 ▼
       PERCEPTION BRAIN                   CONTROL BRAIN
          Zybo Z7                         STM32F103
        Zynq-7000
             │                                 │
       ┌─────┴─────┐                   ┌───────┴────────┐
       │           │                   │                │
 Cortex-A9       FPGA                Sensors         Control
    PS             PL                  │                │
       │           │                   │                │
       │      Camera pipeline       Ultrasonic         PID
       │      Edge detection       IR sensors       State-space
       │      Filtering            Encoders          Navigation
       │      Acceleration             │                │
       │           │                   │                │
       └─────┬─────┘                   └───────┬────────┘
             │                                 │
             │       UART / SPI                │
             └────────────────────────────────►│
                                               │
                                      ┌────────┴────────┐
                                      │                 │
                                     PWM              GPIO
                                      │                 │
                                      └────────┬────────┘
                                               ▼
                                          Motor Driver
                                               │
                                         ┌─────┴─────┐
                                         ▼           ▼
                                    Left Motor   Right Motor
