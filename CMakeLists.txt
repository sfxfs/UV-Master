cmake_minimum_required(VERSION 3.5)
project(UV-Master)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/lib)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS_DEBUG  "-O0 -g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-O3 -w")

add_subdirectory(drivers)
add_subdirectory(log-sys)
add_subdirectory(protocols)
add_subdirectory(user)
add_subdirectory(utils)

add_executable(uvmaster user/main.c)

target_link_libraries(uvmaster
						uvUser
 						uvDrivers
						uvLogSys
						uvProtocols
						uvUtils
						pthread
						i2c
						gpiod
						ev)
