project(UVM-src::dev)

add_library(${PROJECT_NAME} STATIC xxx.c)
add_library(src::libdev ALIAS ${PROJECT_NAME})
