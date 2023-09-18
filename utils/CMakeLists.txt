cmake_minimum_required(VERSION 3.5)

aux_source_directory(. srcs)

add_library(rovUtils SHARED
			${srcs})
