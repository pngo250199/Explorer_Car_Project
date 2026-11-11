#######################################################################
# CMakeLists.txt
# Project : Explorer_car
# Target  : STM32F103C8T6 Blue Pill
# Core    : ARM Cortex-M3
#######################################################################

cmake_minimum_required(VERSION 3.20)

project(Explorer_car LANGUAGES C ASM)

# Generate compile_commands.json for VS Code IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#######################################################################
# MCU SETTINGS
#######################################################################

set(MCPU "-mcpu=cortex-m3")
set(MFLOAT_ABI "-mfloat-abi=soft")

#######################################################################
# STM32CUBE F1 LOCATION
#######################################################################

set(STM32CUBE_F1
    ${CMAKE_SOURCE_DIR}/stm32cubef1/STM32Cube_FW_F1_V1.8.0
)

#######################################################################
# LINKER SCRIPT
#######################################################################

set(LINKER_SCRIPT
    ${CMAKE_SOURCE_DIR}/STM32F103C8TX_FLASH.ld
)

#######################################################################
# SOURCE FILES
#######################################################################

set(PROJECT_SOURCES

    # Startup
    ${CMAKE_SOURCE_DIR}/Startup/startup_stm32f103c8tx.s

    # Application
    ${CMAKE_SOURCE_DIR}/Sources/main.c

    # Firmware drivers
    ${CMAKE_SOURCE_DIR}/Sources/Firmwares_sources/uart.c

    # CMSIS system file
    ${STM32CUBE_F1}/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c

    # Newlib support
    ${CMAKE_SOURCE_DIR}/Sources/syscalls.c
    ${CMAKE_SOURCE_DIR}/Sources/sysmem.c
)

#######################################################################
# EXECUTABLE
#######################################################################

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    SUFFIX ".elf"
)

#######################################################################
# STM32 DEVICE DEFINITION
#######################################################################

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    STM32F103xB
)

#######################################################################
# INCLUDE DIRECTORIES
#######################################################################

target_include_directories(${PROJECT_NAME}
    PRIVATE

    # CMSIS Cortex-M core headers
    ${STM32CUBE_F1}/Drivers/CMSIS/Include

    # STM32F1 device headers
    ${STM32CUBE_F1}/Drivers/CMSIS/Device/ST/STM32F1xx/Include

    # Your own firmware headers
    ${CMAKE_SOURCE_DIR}/Inc/Firmwares_headers
)

#######################################################################
# COMPILER OPTIONS
#######################################################################

target_compile_options(${PROJECT_NAME}
    PRIVATE

    ${MCPU}
    ${MFLOAT_ABI}
    -mthumb

    $<$<COMPILE_LANGUAGE:C>:-std=gnu11>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>

    -ffunction-sections
    -fdata-sections
)

#######################################################################
# ASSEMBLER OPTIONS
#######################################################################

target_compile_options(${PROJECT_NAME}
    PRIVATE

    $<$<COMPILE_LANGUAGE:ASM>:-x>
    $<$<COMPILE_LANGUAGE:ASM>:assembler-with-cpp>
)

#######################################################################
# LINKER OPTIONS
#######################################################################

target_link_options(${PROJECT_NAME}
    PRIVATE

    ${MCPU}
    ${MFLOAT_ABI}
    -mthumb

    -T${LINKER_SCRIPT}

    --specs=nano.specs
    --specs=nosys.specs

    -static

    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map

    -Wl,--start-group
    -lc
    -lm
    -Wl,--end-group
)

#######################################################################
# SHOW FLASH / RAM USAGE AFTER BUILD
#######################################################################

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD

    COMMAND ${CMAKE_SIZE}
            $<TARGET_FILE:${PROJECT_NAME}>
)

#######################################################################
# GENERATE .HEX AND .BIN FILES
#######################################################################

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD

    COMMAND ${CMAKE_OBJCOPY}
            -O ihex
            $<TARGET_FILE:${PROJECT_NAME}>
            ${PROJECT_NAME}.hex

    COMMAND ${CMAKE_OBJCOPY}
            -O binary
            $<TARGET_FILE:${PROJECT_NAME}>
            ${PROJECT_NAME}.bin
)