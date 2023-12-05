project(uvm-cfg)

add_library(${PROJECT_NAME} SHARED uvm-hal.c)
add_library(libcfg ALIAS ${PROJECT_NAME})
