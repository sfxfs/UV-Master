project(uvm-hal)

aux_source_directory(drv drv_srcs)
aux_source_directory(intf intf_srcs)
aux_source_directory(utils utils_srcs)

add_library(${PROJECT_NAME} SHARED  ${intf_srcs}
                                    ${drv_srcs}
                                    ${utils_srcs}
                                    driver_ms5837_basic.c
                                    driver_pca9685_basic.c)
add_library(libhal ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        .
        ./drv
        ./intf
        ./utils
)
