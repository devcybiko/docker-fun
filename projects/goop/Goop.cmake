add_library(Goop INTERFACE)

target_sources(Goop INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/Goop.c
    ${CMAKE_CURRENT_LIST_DIR}/GObj.c
    ${CMAKE_CURRENT_LIST_DIR}/GList.c
    ${CMAKE_CURRENT_LIST_DIR}/GMap.c
)

target_include_directories(Goop INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(Goop INTERFACE
    pico_stdlib
)