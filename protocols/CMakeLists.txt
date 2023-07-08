cmake_minimum_required(VERSION 3.5)

add_library(rovProtocols SHARED
		cJSON.c
		jsonrpc-c.c
		picohttpparser.c)
