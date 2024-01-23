project(uvm-cfg)

aux_source_directory(params cfg_srcs)
aux_source_directory(cjson cj_srcs)

add_library(${PROJECT_NAME} SHARED
            uvm-cfg.c
            ${cfg_srcs}
            ${cj_srcs})
add_library(libcfg ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        .
        ../src
        ../cal
        ../hal
)
