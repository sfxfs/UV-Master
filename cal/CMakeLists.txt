project(UVM-cal)

add_library(${PROJECT_NAME} SHARED uvm-cal.c)
add_library(libcal ALIAS ${PROJECT_NAME})
