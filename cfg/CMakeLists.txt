project(uvm-cfg)

aux_source_directory(params cfg_srcs)

add_library(${PROJECT_NAME} SHARED
            uvm-cfg.c
            ${cfg_srcs})
add_library(libcfg ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ../exlibs/cJSON
        ../exlibs/struct2json
)
