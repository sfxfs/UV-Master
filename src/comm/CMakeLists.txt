project(UVM-src-comm)

add_library(${PROJECT_NAME} STATIC xxx.c)
add_library(src::libcomm ALIAS ${PROJECT_NAME})
