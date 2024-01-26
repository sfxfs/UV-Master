project(uvm-cal)

add_library(${PROJECT_NAME} SHARED
            uvm_cal.c
            rpc_cjson.c
            tcp_server.c)

target_link_libraries(${PROJECT_NAME}
                        cjson
                        pthread)

target_include_directories(${PROJECT_NAME} PUBLIC
                            ../3rd/cjson
                            ../3rd/clog)
