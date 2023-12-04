project(UVM-hal)

add_library(${PROJECT_NAME} SHARED uvm-hal.c)
add_library(libhal ALIAS ${PROJECT_NAME})
