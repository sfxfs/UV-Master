cmake_minimum_required(VERSION 3.5)
project(UV-Master)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/lib)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS_DEBUG   "-O0 -g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-O3 -w -DNDEBUG")

include_directories(3rd/cjson
                    3rd/clog
                    3rd/s2j)

add_subdirectory(3rd)
add_subdirectory(hal)
add_subdirectory(cal)
add_subdirectory(cfg)
add_subdirectory(user)
