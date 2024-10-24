project(uvm-cal)

add_library(${PROJECT_NAME} SHARED
            uvm_cal.c
            mjsonrpc.c
            tcp_server.c)

target_link_libraries(${PROJECT_NAME}
                        cjson
                        pthread)
