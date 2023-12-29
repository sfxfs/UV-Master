project(UVM-src-rpc)

add_library(${PROJECT_NAME} STATIC info.c)
add_library(src::librpc ALIAS ${PROJECT_NAME})
