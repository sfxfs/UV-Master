project(UVM-src-rpc)

add_library(${PROJECT_NAME} STATIC xxx.c)
add_library(src::librpc ALIAS ${PROJECT_NAME})
