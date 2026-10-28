1. Project diagram
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
