project(uvm-user-ctrl)

add_library(${PROJECT_NAME} STATIC
            mode_manual.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ../dev
        ../rpc
        ../../cal
        ../../cfg
        ../../hal
        ../../3rd/clog
)
