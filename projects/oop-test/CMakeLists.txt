cmake_minimum_required(VERSION 3.14)
include(pico_sdk_import.cmake)
project(oop-test VERSION 1.0.0)
add_executable(oop-test
               main.c)

pico_sdk_init()

pico_enable_stdio_usb(oop-test 1)
pico_enable_stdio_uart(oop-test 1)
pico_add_extra_outputs(oop-test)

target_link_libraries(oop-test
                      pico_stdlib
                      hardware_gpio
                      hardware_i2c
                      hardware_spi
                      hardware_adc
                      hardware_uart)
