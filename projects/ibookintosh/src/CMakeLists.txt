print_variables(" ./src/CmakeLists.txt")

add_executable(${NAME} main.c)

pico_enable_stdio_usb(${NAME} 0)
pico_enable_stdio_uart(${NAME} 1)
pico_add_extra_outputs(${NAME})

target_link_libraries(${NAME}
                      pico_stdlib
                      hardware_gpio
                      hardware_i2c
                      hardware_spi
                      hardware_adc
                      hardware_uart
                      Goop 
                      Gtos 
                      Tps65 
)
