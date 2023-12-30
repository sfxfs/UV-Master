project(uvm-src-ctrl)

add_library(${PROJECT_NAME} STATIC mode_manual.c)
add_library(src::libctrl ALIAS ${PROJECT_NAME})
