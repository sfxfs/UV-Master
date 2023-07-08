cmake_minimum_required(VERSION 3.5)

aux_source_directory(control control_srcs)
aux_source_directory(device device_srcs)
aux_source_directory(server server_srcs)

add_library(rovUser SHARED
		main.c
		${control_srcs}
		${device_srcs}
		${server_srcs})
