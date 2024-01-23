project(uvm-src)

add_subdirectory(rpc)
add_subdirectory(ctrl)
add_subdirectory(dev)
add_subdirectory(log)

add_executable(uvmaster main.c)

target_link_libraries(uvmaster
    libhal
    libcal
    libcfg
    pthread
    m
)

target_include_directories(uvmaster
    PUBLIC
        .
        ..
)
