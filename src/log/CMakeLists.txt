project(UVM-src::log)

add_library(${PROJECT_NAME} STATIC xxx.c)
add_library(src::liblog ALIAS ${PROJECT_NAME})
