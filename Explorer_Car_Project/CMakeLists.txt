cmake_minimum_required(VERSION 4.2)

# ADD THIS LINE HERE:
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(EmbeddedProject C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_SYSTEM_NAME Generic)

add_executable(${PROJECT_NAME} 
Src/main.c
Src/gpio.c
Src/spi.c
Src/tim.c
Src/SysTick.c)
# Add this line right after the add_executable line
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")
target_include_directories(${PROJECT_NAME} PUBLIC include)

# ADD THESE FLAGS FOR BARE METAL:
target_compile_options(${PROJECT_NAME} PUBLIC "--specs=nosys.specs")
target_link_options(${PROJECT_NAME} PUBLIC "--specs=nosys.specs")

target_include_directories(${PROJECT_NAME} PUBLIC 
    include
    Inc/Firmwares_headers
    chip_headers
    chip_headers/CMSIS/Include
    chip_headers/CMSIS/Device/ST/STM32F4xx/Include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    STM32F411xE
)
