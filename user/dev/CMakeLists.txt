project(uvm-user-dev)

add_library(${PROJECT_NAME} STATIC
            motor.c
            sensor.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ../ctrl
        ../rpc
        ../../cal
        ../../cfg
        ../../hal
        ../../3rd/clog
)
