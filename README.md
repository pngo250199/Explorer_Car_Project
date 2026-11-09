

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


```


# Autonomous Explorer Car

## Project Overview

This project is a heterogeneous embedded-system platform for developing and evaluating autonomous sensing, image processing, and real-time control.

The system combines:

- **STM32F103 microcontroller** for low-level real-time sensing and actuator control
- **Zynq-7000 SoC** for higher-level software and FPGA hardware acceleration
- **ARM Cortex-A9** for software control and system coordination
- **FPGA programmable logic** for parallel computation and image-processing acceleration

The project is being developed incrementally. The current goal is not yet to demonstrate a fully autonomous vehicle, but to build and validate the hardware/software architecture required for future autonomous operation.

The system will eventually be used to measure performance such as:

- Sensor-to-control reaction time
- Processing latency
- CPU tick counts
- PWM response time
- Pure C execution time
- ARM NEON/SIMD execution time
- FPGA hardware-acceleration execution time

---

# System Architecture

The current planned architecture is:

```text
                 Camera
                    |
                    v
          +-------------------+
          |    Zynq-7000      |
          |                   |
          |  Cortex-A9        |
          |  - Software       |
          |  - Coordination   |
          |  - AXI control    |
          |                   |
          |  FPGA Logic       |
          |  - Image process  |
          |  - Acceleration   |
          +---------+---------+
                    |
               UART / SPI
                    |
                    v
          +-------------------+
          |    STM32F103      |
          |                   |
          |  Sensors          |
          |  PWM              |
          |  Motors           |
          |  Servo            |
          |  Safety control   |
          +---------+---------+
                    |
                    v
                 Vehicle
```

The architecture separates tasks according to the strengths of each device.

### STM32F103

The STM32 is responsible for deterministic, low-level real-time control.

Planned responsibilities include:

- Ultrasonic and IR sensor acquisition
- Motor control
- PWM generation
- Servo control
- Real-time obstacle response
- Safety behavior
- Communication with the Zynq platform

### ARM Cortex-A9

The Cortex-A9 operates as the main software controller on the Zynq platform.

Its responsibilities include:

- Configuring FPGA hardware through AXI
- Running software image-processing implementations
- Running ARM NEON/SIMD implementations
- Reading accelerator status and results
- Measuring execution time
- Coordinating data with the STM32

### FPGA Programmable Logic

The FPGA is intended for computationally intensive and highly parallel workloads.

Planned FPGA workloads include:

- Grayscale conversion
- Edge detection
- Parallel pixel processing
- Camera/video pipelines
- Future custom image-processing accelerators

---

# Development Environment

The project is currently developed using:

- AMD Vivado 2026.1
- AMD Vitis 2026.1
- Verilog HDL
- Bare-metal C
- CMake
- GNU Arm Embedded Toolchain
- Git / GitHub

The project has been successfully configured and tested on both:

- Linux
- Windows

This allows development to continue from either machine using the same Git repository.

---

# Milestone 1 - Zynq Hardware/Software Communication

The first completed milestone was establishing communication between the ARM Cortex-A9 and custom FPGA logic.

A custom AXI4-Lite peripheral was created in Vivado and connected to the Zynq Processing System.

The communication architecture is:

```text
ARM Cortex-A9
      |
      | AXI4-Lite
      v
AXI SmartConnect
      |
      v
Custom FPGA IP
      |
      v
GPIO
```

This was the first hardware/software co-design validation for the project.

---

# Custom AXI4-Lite Peripheral

The custom FPGA peripheral contains memory-mapped registers that can be accessed by software running on the Cortex-A9.

The current base address is:

```text
0x43C00000
```

The initial register map is:

| Offset | Address | Function |
| --- | --- | --- |
| `0x00` | `0x43C00000` | Switch / input register |
| `0x04` | `0x43C00004` | LED / output register |

The first register returns the state of the physical FPGA switches.

The second register controls the physical LEDs.

---

# FPGA GPIO Implementation

The custom IP exposes FPGA GPIO signals:

```verilog
input wire [3:0] gpio_in;
output wire [3:0] gpio_out;
```

The output logic currently connects the lower four bits of AXI slave register 1 to the LEDs:

```verilog
assign gpio_out = slv_reg1[3:0];
```

The lower four bits of the first register's read path are connected to the physical switch inputs.

Conceptually:

```text
Switches
   |
   v
gpio_in
   |
   v
AXI Register 0
```

and:

```text
AXI Register 1
   |
   v
gpio_out
   |
   v
LEDs
```

---

# Cortex-A9 Software

The Cortex-A9 accesses the FPGA through memory-mapped I/O.

Example:

```c
#include <stdint.h>
#include "xparameters.h"

int main(void)
{
    volatile uint32_t value;

    while (1)
    {
        value = *(volatile uint32_t *)
                (XPAR_CUSTOMIP_0_BASEADDR + 0x00U);

        *(volatile uint32_t *)
        (XPAR_CUSTOMIP_0_BASEADDR + 0x04U) = value;
    }

    return 0;
}
```

The software performs the following operation:

```text
Read switch register
        |
        v
Cortex-A9
        |
        v
Write LED register
        |
        v
LED state changes
```

---

# Hardware Validation

The first direct hardware validation was performed by writing:

```c
*(volatile uint32_t *)
(XPAR_CUSTOMIP_0_BASEADDR + 0x04U) = 0xFU;
```

`0xF` corresponds to:

```text
1111
```

Therefore all four FPGA LEDs were expected to turn on.

The test successfully turned on all four LEDs.

This verified the complete path:

```text
C Software
    |
    v
Cortex-A9
    |
    v
AXI4-Lite
    |
    v
Custom FPGA Register
    |
    v
Programmable Logic
    |
    v
Physical LED
```

This was an important milestone because it confirmed that software running on the ARM processor can successfully control custom FPGA hardware.

---

# Debugging and Integration Work

Several hardware/software integration issues were identified and resolved during development.

## Stale Custom IP Output

Changes made to the custom IP source were initially not reflected in the generated FPGA design.

The issue was caused by Vivado using an older generated copy of the custom IP.

The solution was to:

```text
Modify custom IP source
        |
        v
Re-package / update IP
        |
        v
Regenerate output products
        |
        v
Synthesis
        |
        v
Implementation
        |
        v
Generate new bitstream
```

This confirmed the importance of keeping packaged IP synchronized with its RTL source.

---

## AXI Multiple-Driver Error

During Git conflict resolution, two separate assignments to `S_AXI_RDATA` were accidentally retained.

This produced a Vivado:

```text
MDRV-1 Multiple Driver Nets
```

error.

The issue was resolved by ensuring that only one read-data assignment drove the AXI output.

This became an important project rule:

> A Git merge that has no conflict markers is not necessarily logically correct RTL.

Hardware designs must still be rebuilt and validated after merge resolution.

---

# Cross-Platform Development

The project is now operational on both Linux and Windows.

The development workflow is:

```text
GitHub
  ^
  |
  +-------- Linux
  |
  +-------- Windows
```

Before beginning work on either machine:

```bash
git pull --rebase origin main
```

After completing and testing changes:

```bash
git add <modified source files>
git commit -m "description"
git push origin main
```

Generated Vivado and Vitis files are intentionally excluded from Git.

Examples include:

```text
Vivado .gen/
Vivado .runs/
Vivado .cache/
Vitis build/
Vitis _ide/
bitstreams
generated BSP files
```

The repository instead tracks the source files required to regenerate the system.

---

# Current Project Status

## Completed

- STM32 development environment
- Basic STM32 peripheral drivers
- Zynq-7000 Vivado project
- Cortex-A9 processing system configuration
- Custom AXI4-Lite peripheral
- AXI SmartConnect integration
- AXI memory map
- Custom FPGA GPIO
- Physical switch input
- Physical LED output
- Bare-metal Cortex-A9 application
- ARM-to-FPGA communication
- Vivado bitstream generation
- Vitis application execution
- Linux development environment
- Windows development environment
- GitHub cross-platform workflow

---

# Current FPGA Milestone

The current verified hardware/software architecture is:

```text
Cortex-A9
    |
AXI4-Lite
    |
Custom FPGA IP
    |
GPIO
```

This establishes the control interface that will later be reused for more advanced FPGA accelerators.

---

# Next Development Stage

The next major stage is image-processing integration.

Instead of using the FPGA only for GPIO control, custom FPGA logic will process image data.

Target architecture:

```text
Camera
   |
   v
Video Input
   |
   v
FPGA Image Processing
   |
   +--> Grayscale
   |
   +--> Edge Detection
   |
   +--> Future accelerators
   |
   v
Processed Result
   |
   v
Cortex-A9
```

AXI4-Lite will continue to be used for accelerator configuration and status.

High-bandwidth image data will use a streaming or memory-based interface rather than AXI4-Lite.

---

# Performance Evaluation

An important objective of this project is to compare different processing architectures.

Planned implementations include:

```text
Pure C
   vs.
ARM NEON / SIMD
   vs.
FPGA Hardware Acceleration
```

Measurements will include:

- Processor ticks
- Execution time
- Frame-processing latency
- Sensor-to-control latency

The STM32 portion will also be evaluated for real-time response.

For example:

```text
Obstacle detected
      |
      v
Sensor reading
      |
      v
Control decision
      |
      v
PWM updated
```

The time between obstacle detection and the PWM update can be measured to evaluate real-time response.

---

# Long-Term Goal

The long-term goal is to integrate the FPGA vision system and STM32 real-time controller into one heterogeneous embedded platform.

The final architecture is expected to demonstrate that different processors are better suited to different workloads:

- **STM32:** deterministic real-time sensing and control
- **Cortex-A9:** software processing and system coordination
- **FPGA:** parallel hardware acceleration

Rather than attempting to execute every task on one processor, the project explores how hardware and software can be partitioned across different processing resources to improve overall system performance.
