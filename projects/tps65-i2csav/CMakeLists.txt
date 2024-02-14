cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-tps65)

pico_sdk_init()

add_executable(tps65
    tps65.c
)

target_link_libraries(tps65
    pico_stdlib
    hardware_i2c
)

pico_enable_stdio_usb(tps65 1)
pico_enable_stdio_uart(tps65 0)

pico_add_extra_outputs(tps65)
