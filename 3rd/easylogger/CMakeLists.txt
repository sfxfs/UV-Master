cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG  "-O0 -g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-O3 -w")
set(CMAKE_VERBOSE_MAKEFILE ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(./inc)
include_directories(./plugins)

set(srcs
        plugins/file/elog_file_port.c
        plugins/file/elog_file.c
        port/elog_port.c
        src/elog_async.c
        src/elog_buf.c
        src/elog_utils.c
        src/elog.c)
add_library(easylogger SHARED ${srcs})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
