cmake_minimum_required(VERSION 4.2)

# ADD THIS LINE HERE:
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(EmbeddedProject C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_SYSTEM_NAME Generic)

# Set common architecture flags
set(ARCH_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# Apply to both C and ASM
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${ARCH_FLAGS} -x assembler-with-cpp")

add_executable(${PROJECT_NAME} 
startup/startup_stm32f4xx.s
Src/main.c
Src/Firmware_Sources/gpio.c
Src/Firmware_Sources/spi.c
Src/Firmware_Sources/tim.c
Src/Firmware_Sources/SysTick.c)
# Add this line right after the add_executable line
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")

# ADD THESE FLAGS FOR BARE METAL:
target_compile_options(${PROJECT_NAME} PUBLIC "--specs=nosys.specs")
target_link_options(${PROJECT_NAME} PUBLIC 
    "--specs=nosys.specs"
    "-nostartfiles"
    "-T${CMAKE_SOURCE_DIR}/linker/stm32f411.ld"
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    Inc/Firmwares_headers
    chip_headers
    chip_headers/CMSIS/Include
    chip_headers/CMSIS/Device/ST/STM32F4xx/Include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    STM32F411xE
)
