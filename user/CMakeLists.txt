aux_source_directory(rpc rpc_srcs)
aux_source_directory(ctrl ctrl_srcs)
aux_source_directory(dev dev_srcs)

add_executable(uvmaster main.c
                        ${dev_srcs}
                        ${ctrl_srcs}
                        ${rpc_srcs})

target_link_libraries(uvmaster
    m
    pthread
    cjson
    clog
    s2j
    uvm-cal
    uvm-cfg
    uvm-hal
)

target_include_directories(uvmaster PUBLIC
                            .
                            ../cal
                            ../cfg
                            ../hal
                            ../3rd/clog
                            ../3rd/cjson
                            )
