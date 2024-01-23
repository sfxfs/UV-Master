project(uvm-src)

add_subdirectory(rpc)
add_subdirectory(ctrl)
add_subdirectory(dev)
add_subdirectory(log)

add_executable(uvmaster main.c)

target_link_libraries(uvmaster
    pthread
    m
    src::libctrl
    src::libdev
    src::liblog
    src::librpc
    libhal
    libcfg
    libcal
)

target_include_directories(uvmaster
    PUBLIC
        .
        ..
)
