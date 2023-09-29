cmake_minimum_required(VERSION 3.5)

aux_source_directory(. srcs)
aux_source_directory(libmelon melon_srcs)

add_library(uvUtils SHARED
			${srcs}
			${melon_srcs})
