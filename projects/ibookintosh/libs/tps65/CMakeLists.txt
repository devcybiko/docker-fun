print_variables("./lib/tps65")
add_library(Tps65 INTERFACE)

target_sources(Tps65 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Tps65.c
)

target_include_directories(Tps65 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Tps65 INTERFACE
    pico_stdlib
)