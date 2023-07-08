cmake_minimum_required(VERSION 3.5)

add_library(rovDrivers SHARED
			ms5837.c
			pca9685.c)
