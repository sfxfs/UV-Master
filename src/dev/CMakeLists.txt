project(uvm-src-dev)

add_library(${PROJECT_NAME} STATIC
            motor.c
            sensor.c)
add_library(src::libdev ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ..
        ../../cal
        ../../cfg
        ../../hal
)
