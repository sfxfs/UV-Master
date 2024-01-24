project(uvm-cfg)

add_library(${PROJECT_NAME} SHARED
            uvm_cfg.c
            cfg_dev_ctl.c
            cfg_others.c
            cfg_propeller.c
            cfg_rocket_ratio.c)

target_include_directories(${PROJECT_NAME} PUBLIC
                            ../3rd/cjson
                            ../3rd/s2j)
