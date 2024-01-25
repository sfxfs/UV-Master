project(uvm-user-rpc)

add_library(${PROJECT_NAME} STATIC
            info.c
            ctrl.c
            debug.c
            rpc_fun.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ../dev
        ../ctrl
        ../../cal
        ../../cfg
        ../../hal
        ../../3rd/clog
        ../../3rd/cjson
)
