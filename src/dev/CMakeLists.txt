project(UVM-src-dev)

add_library(${PROJECT_NAME} STATIC
            motor.c
            sensor.c)
add_library(src::libdev ALIAS ${PROJECT_NAME})
