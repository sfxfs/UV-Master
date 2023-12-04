project(UVM-src::ctrl)

add_library(${PROJECT_NAME} STATIC xxx.c)
add_library(src::libctrl ALIAS ${PROJECT_NAME})
