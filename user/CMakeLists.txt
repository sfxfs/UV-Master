cmake_minimum_required(VERSION 3.5)

include_directories(../protocols)
include_directories(../log-sys)
include_directories(../drivers)
include_directories(../utils)
include_directories(../utils/libmelon)

include_directories(.)

aux_source_directory(control control_srcs)
aux_source_directory(control/ctrlPart ctrlPart_srcs)

aux_source_directory(device device_srcs)
aux_source_directory(device/application application_srcs)
aux_source_directory(device/interface interface_srcs)

aux_source_directory(server/handler handler_srcs)
aux_source_directory(server server_srcs)

aux_source_directory(config config_srcs)
aux_source_directory(config/parameters parameters_srcs)

add_library(uvUser STATIC
        	main_app.c
			${control_srcs}
			${ctrlPart_srcs}
			${application_srcs}
			${device_srcs}
			${interface_srcs}
			${handler_srcs}
			${server_srcs}
			${config_srcs}
			${parameters_srcs})
