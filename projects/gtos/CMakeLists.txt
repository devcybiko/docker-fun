print_variables(".lib/gtos")
add_library(Gtos INTERFACE)

target_sources(Gtos INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/GCron.c
    ${CMAKE_CURRENT_SOURCE_DIR}/GCronEntry.c
    ${CMAKE_CURRENT_SOURCE_DIR}/GTimer.c
)

target_include_directories(Gtos INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Gtos INTERFACE
    pico_stdlib
)