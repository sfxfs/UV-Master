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
)

target_include_directories(uvmaster PUBLIC
                            ../cal
                            ../hal
                            ../cfg)
