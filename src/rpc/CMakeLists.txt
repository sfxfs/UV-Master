project(uvm-src-rpc)

add_library(${PROJECT_NAME} STATIC info.c
                                    ctrl.c
                                    debug.c)
add_library(src::librpc ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ..
        ../../cal
        ../../cfg
        ../../hal
)
