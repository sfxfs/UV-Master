project(uvm-user-rpc)

add_library(${PROJECT_NAME} STATIC
            info.c
            ctrl.c
            debug.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ../dev
        ../ctrl
        ../../cal
        ../../cfg
        ../../hal
        ../../3rd/clog
)
