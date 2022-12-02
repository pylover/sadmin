cmake_minimum_required(VERSION 3.7)
project(sadmin 
    VERSION 1.0.0
    LANGUAGES C
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fms-extensions -D_GNU_SOURCE=1")


configure_file(manifest.h.in manifest.h)
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)


add_library(ev OBJECT ev.c)
add_library(serial OBJECT serial.c)

add_executable(sadmin 
    $<TARGET_OBJECTS:ev> 
    $<TARGET_OBJECTS:serial> 
    main.c
)
target_include_directories(sadmin PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(sadmin PUBLIC m clog)
