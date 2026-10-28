1. Project diagram
```text
Car Explorer
├── Brain
│   ├── STM32F4
│   └── Cortex-M
│
├── Sensors
│   ├── I2C touchless sensor
│   └── Ultrasonic
│
├── Firmwares
│   ├── SPI
│   ├── GPIO
│   ├── Timer
│   ├── TIM2
│   └── SysTick / Interrupt
│
├── Connections
│   ├── Main control
│   ├── GPIO
│   ├── DC motors
│   ├── Signal GPIO
│   └── PWM
│
└── Software
    ├── Low-C
    ├── CMake
    └── Rust (optional)```
