project(uvm-cal)

add_library(${PROJECT_NAME} SHARED
			uvm-cal.c
            tcp-server.c
            rpc-fun.c
            rpc-cjson.c)
add_library(libcal ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        .
        ../src
        ../cfg
        ../hal
)
