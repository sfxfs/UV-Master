cmake_minimum_required(VERSION 3.5)

include_directories(../protocols)
include_directories(../drivers)

aux_source_directory(control control_srcs)
aux_source_directory(device device_srcs)
aux_source_directory(device/interface interface_srcs)
aux_source_directory(server server_srcs)

add_library(rovUser STATIC
			${control_srcs}
			${device_srcs}
			${interface_srcs}
			${server_srcs})
