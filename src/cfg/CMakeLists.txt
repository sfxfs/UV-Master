project(UVM-src-cfg)

add_library(${PROJECT_NAME} STATIC xxx.c)
add_library(src::libcfg ALIAS ${PROJECT_NAME})
