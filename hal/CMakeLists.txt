project(uvm-hal)

aux_source_directory(utils utils_srcs)

add_library(${PROJECT_NAME} SHARED
            ${utils_srcs}
            driver_ms5837.c
            interface_ms5837.c
            ms5837.c
            driver_pca9685.c
            interface_pca9685.c
            pca9685.c)

target_link_libraries(${PROJECT_NAME} m)
