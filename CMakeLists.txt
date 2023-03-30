cmake_minimum_required(VERSION 3.14)

set(PICO_BOARD adafruit_feather_rp2040)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)

project(SensorMotor VERSION 1.0.0 LANGUAGES C CXX ASM)

set (PICO_CXX_ENABLE_EXCEPTIONS 1)
set (PICO_CXX_ENABLE_RTTI 1)

pico_sdk_init()

set (PICO_SDK_FREERTOS_SOURCE /Users/jenna-luzpura/Desktop/Dev/Courses/S23/CS452/pico/FreeRTOS-Kernel)

add_library(
    freertos
    ${PICO_SDK_FREERTOS_SOURCE}/event_groups.c
    ${PICO_SDK_FREERTOS_SOURCE}/list.c
    ${PICO_SDK_FREERTOS_SOURCE}/queue.c
    ${PICO_SDK_FREERTOS_SOURCE}/stream_buffer.c
    ${PICO_SDK_FREERTOS_SOURCE}/tasks.c
    ${PICO_SDK_FREERTOS_SOURCE}/timers.c
    ${PICO_SDK_FREERTOS_SOURCE}/portable/MemMang/heap_3.c
    ${PICO_SDK_FREERTOS_SOURCE}/portable/GCC/ARM_CM0/port.c
)

target_include_directories(
    freertos PUBLIC
    include/public
    include/private
    ${PICO_SDK_FREERTOS_SOURCE}/include
    ${PICO_SDK_FREERTOS_SOURCE}/portable/GCC/ARM_CM0
    )

add_executable(
    ${CMAKE_PROJECT_NAME}
    source/main.cpp
    source/button.cpp
    source/display.cpp
    source/display_driver.cpp
    source/motor.cpp
    source/motor_driver.cpp
    source/pixel.cpp
    source/sensor.cpp
    source/sensor_driver.cpp
    source/system_error.cpp
    source/WS2812.cpp
    )

pico_generate_pio_header(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/source/WS2812.pio)
pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    freertos
    pico_stdlib
    hardware_adc
    hardware_gpio
    hardware_i2c
    hardware_pio
    )

pico_add_extra_outputs(${CMAKE_PROJECT_NAME})
