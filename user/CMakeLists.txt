add_subdirectory(rpc)
add_subdirectory(ctrl)
add_subdirectory(dev)

add_executable(uvmaster main.c)

target_link_libraries(uvmaster
    m
    pthread
    cjson
    clog
    s2j
    uvm-cal
    uvm-cfg
    uvm-hal
    uvm-user-rpc
    uvm-user-dev
    uvm-user-ctrl
)

target_include_directories(uvmaster PUBLIC
                            ../cal
                            ../cfg
                            ../3rd/clog
                            )
