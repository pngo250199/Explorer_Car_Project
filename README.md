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
