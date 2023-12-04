project(UVM-hal)

add_library(${PROJECT_NAME} SHARED xxx.c)
add_library(libhal ALIAS ${PROJECT_NAME})
