cmake_minimum_required(VERSION 3.5)

include_directories(../protocols)
include_directories(../log-sys)
include_directories(../drivers)

aux_source_directory(control control_srcs)
aux_source_directory(control/ctrlPart ctrlPart_srcs)

aux_source_directory(device device_srcs)
aux_source_directory(device/application application_srcs)
aux_source_directory(device/interface interface_srcs)

aux_source_directory(server server_srcs)

aux_source_directory(config config_srcs)
aux_source_directory(config/parameters parameters_srcs)

aux_source_directory(utils utils_srcs)

add_library(rovUser STATIC
        	main_app.c
			${control_srcs}
			${ctrlPart_srcs}
			${application_srcs}
			${device_srcs}
			${interface_srcs}
			${server_srcs}
			${config_srcs}
			${parameters_srcs}
			${utils_srcs})
