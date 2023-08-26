cmake_minimum_required(VERSION 3.5)
project(ROV-Master)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(3rd/easylogger/inc)
include_directories(3rd/libev)
include_directories(3rd/WiringNP/wiringPi)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS_DEBUG  "-O0 -g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-O3 -w")

add_subdirectory(drivers)
add_subdirectory(protocols)
add_subdirectory(user)

add_executable(rovmaster user/rovmain.c)

target_link_libraries(rovmaster
						rovUser
 						rovDrivers
						rovProtocols
						pthread
						wiringPi
						ev
						easylogger)
