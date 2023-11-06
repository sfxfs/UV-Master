cmake_minimum_required(VERSION 3.5)

add_library(uvProtocols SHARED
			cJSON.c
			rpc_cjson.c)
