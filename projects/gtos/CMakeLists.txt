cmake_minimum_required(VERSION 3.14)
include(pico_sdk_import.cmake)
project(gtos VERSION 1.0.0)

add_definitions(-DPICO=1)

add_executable(gtos
	main.c GObj.c GList.c GTimer.c GCron.c
)

pico_sdk_init()

pico_enable_stdio_usb(gtos 1)
pico_enable_stdio_uart(gtos 1)
pico_add_extra_outputs(gtos)

target_link_libraries(gtos
                      pico_stdlib
                      hardware_gpio
                      hardware_i2c
                      hardware_spi
                      hardware_adc
                      hardware_uart)
