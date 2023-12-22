project(uvm-src)

add_subdirectory(rpc)
add_subdirectory(ctrl)
add_subdirectory(dev)
add_subdirectory(log)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME}
    libhal
    libcal
    libexlib
    libcfg
    pthread
    m
)
