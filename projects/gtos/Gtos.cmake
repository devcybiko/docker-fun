add_library(Gtos INTERFACE)

target_sources(Gtos INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/GCron.c
    ${CMAKE_CURRENT_LIST_DIR}/GCronEntry.c
    ${CMAKE_CURRENT_LIST_DIR}/GTimer.c
    ${CMAKE_CURRENT_LIST_DIR}/GMap.c
)

target_include_directories(Gtos INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(Gtos INTERFACE
    pico_stdlib
)