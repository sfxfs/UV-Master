project(uvm-src-log)

add_library(${PROJECT_NAME} STATIC log.c)
add_library(src::liblog ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ..
        ../../cal
        ../../cfg
        ../../hal
)
