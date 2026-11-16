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


### Bare-Metal GPIO Configuration

The STM32F103 GPIO peripheral is configured directly through memory-mapped hardware registers without using HAL libraries.

Each GPIO pin uses four configuration bits in either `GPIOx_CRL` or `GPIOx_CRH`.

```text
GPIOx_CRL → GPIO pins 0–7
GPIOx_CRH → GPIO pins 8–15
```

Each pin uses the following four-bit field:

```text
CNF[1:0] MODE[1:0]
```

For pins 0–7, the starting bit position is calculated as:

```text
shift = pin_number × 4
```

For pins 8–15:

```text
shift = (pin_number - 8) × 4
```

For example, PB1 is located in `GPIOB->CRL` and uses bits 7:4:

```c
GPIOB->CRL &= ~(0xFU << 4);
GPIOB->CRL |=  (0x2U << 4);
```

`0xF << 4` creates a mask covering the four PB1 configuration bits. The first statement clears the existing configuration.

`0x2` corresponds to binary `0010`, configuring PB1 as a 2 MHz general-purpose push-pull output. PB1 is used as the HC-SR04 TRIG signal.

PB10 is located in `GPIOB->CRH`. Since CRH starts at pin 8:

```text
(10 - 8) × 4 = 8
```

Therefore PB10 uses bits 11:8:

```c
GPIOB->CRH &= ~(0xFU << 8);
GPIOB->CRH |=  (0x4U << 8);
```

`0x4`, or binary `0100`, configures PB10 as a floating digital input for receiving the HC-SR04 ECHO signal.

### GPIO Data Registers

Unlike CRL and CRH, the input/output registers use one bit per GPIO pin.

For example:

```c
GPIOB->BSRR = (1U << 1);
```

sets PB1 HIGH.

```c
GPIOB->BRR = (1U << 1);
```

sets PB1 LOW.

The input state of PB10 is checked using:

```c
GPIOB->IDR & (1U << 10)
```

The expression `1U << 10` creates a mask containing only bit 10. ANDing the mask with the GPIO input data register determines whether PB10 is HIGH or LOW.

The same technique is used for the IR sensor connected to PB0:

```c
if (!(GPIOB->IDR & (1U << 0)))
{
    /* Obstacle detected */
}
```

The IR module is active-low, so PB0 reads logic 0 when an obstacle is detected and logic 1 when the path is clear.

## Cheat sheet to remember
Configuration register:
4 bits per pin

CRL:
shift = pin × 4

CRH:
shift = (pin - 8) × 4


Input/output registers:
1 bit per pin

mask = 1U << pin

## Next Steps

1. Validate USART2 transmission on PA2.✅
2. Validate USART2 reception on PA3. ✅
3. Develop the ultrasonic sensor driver. ✅
4. Develop the IR obstacle sensor driver. ✅
5. Implement PWM motor control through the L298N.
6. Implement local obstacle-response safety logic.
7. Establish STM32-to-Zybo communication.
