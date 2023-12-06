project(uvm-exlib)

add_library(${PROJECT_NAME} SHARED
            cJSON/cJSON.c
            struct2json/s2j.c)
add_library(libexlib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        cJSON
        struct2json
)
