project(UVM-cal)

add_library(${PROJECT_NAME} SHARED xxx.c)
add_library(libcal ALIAS ${PROJECT_NAME})
