# STM32F103 Safety Controller

This directory contains the STM32F103C8T6 firmware for the Explorer Car project. The STM32 acts as the low-level real-time controller responsible for short-range sensing, motor control, local safety decisions, and future communication with the Zybo Z7 processing platform.

## Development Environment

The firmware is developed as a bare-metal C project using:

- STM32F103C8T6 Blue Pill
- ARM Cortex-M3
- GNU ARM Embedded Toolchain
- CMake
- CMSIS
- STM32CubeF1 device support
- VS Code

The project primarily uses CMSIS and direct register-level peripheral access rather than STM32 HAL.

## Current Status

The STM32 development environment has been configured and successfully tested with a minimal C program.

Completed setup includes:

- ARM Cortex-M3 compiler configuration
- STM32F103C8T6 linker script
- STM32 startup assembly
- STM32CubeF1 CMSIS integration
- `STM32F103xB` device definition
- CMSIS Cortex-M3 core headers
- STM32F1 device headers
- CMake-generated `compile_commands.json`
- VS Code IntelliSense integration
- Initial USART2 driver structure

USART2 hardware communication has not yet been physically validated.

## Project Structure

```text
Explorer_car/
|
+-- CMakeLists.txt
+-- cubeide-gcc.cmake
+-- STM32F103C8TX_FLASH.ld
|
+-- Startup/
|   +-- startup_stm32f103c8tx.s
|
+-- Sources/
|   +-- main.c
|   |
|   +-- Firmwares_sources/
|       +-- uart.c
|
+-- Inc/
|   +-- Firmwares_headers/
|       +-- uart.h
|
+-- stm32cubef1/
    +-- STM32Cube_FW_F1_V1.8.0/
```

## CMSIS Architecture

```text
Application
    |
    v
stm32f1xx.h
    |
    | STM32F103xB
    v
stm32f103xb.h
    |
    v
STM32 Peripheral Registers
    |
    +-- RCC
    +-- GPIO
    +-- USART
    +-- TIM
    +-- SPI
    +-- I2C
```

The `STM32F103xB` compile definition allows the generic `stm32f1xx.h` header to select the correct STM32F103 device header.

## Build

Configure the project:

```bash
cmake \
-DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake \
-S . \
-B Debug \
-G "Unix Makefiles" \
-DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

Build:

```bash
cmake --build Debug
```

The generated firmware will be located in the `Debug` build directory.

## STM32 Role in Explorer Car

```text
Ultrasonic Sensor ---\
                      \
IR Obstacle Sensor ----> STM32F103
                           |
                           +-- Safety Logic
                           +-- PWM Control
                           +-- L298N Motor Driver
                           +-- USART Communication
                                      |
                                      v
                                   Zybo Z7
```

The STM32 will provide deterministic short-range safety control, while the Zybo Z7 handles higher-level image processing and FPGA-accelerated computation.

## Next Steps

1. Validate USART2 transmission on PA2.
2. Validate USART2 reception on PA3.
3. Develop the ultrasonic sensor driver.
4. Develop the IR obstacle sensor driver.
5. Implement PWM motor control through the L298N.
6. Implement local obstacle-response safety logic.
7. Establish STM32-to-Zybo communication.
