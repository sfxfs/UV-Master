project(uvm-cfg)

add_library(${PROJECT_NAME} SHARED
            uvm_cfg.c
            uvm_cfg_intf.c
            cfg_dev_ctl.c
            cfg_others.c
            cfg_propeller.c
            cfg_rocket_ratio.c)

target_link_libraries(${PROJECT_NAME} s2j)

target_include_directories(${PROJECT_NAME} PUBLIC
                            ../3rd/cjson
                            ../3rd/s2j
                            ../3rd/clog)
