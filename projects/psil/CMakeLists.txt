cmake_minimum_required(VERSION 3.14)
include(pico_sdk_import.cmake)
project(psil VERSION 1.0.0)
add_executable(psil
               main.c)

pico_sdk_init()

pico_enable_stdio_usb(psil 1)
pico_enable_stdio_uart(psil 1)
pico_add_extra_outputs(psil)

target_link_libraries(psil
                      pico_stdlib
                      hardware_gpio
                      hardware_i2c
                      hardware_spi
                      hardware_adc
                      hardware_uart)
