cmake_minimum_required(VERSION 3.5)

add_library(rovLogSys SHARED
        elog.c
        elog_async.c
        elog_buf.c
        elog_utils.c)
