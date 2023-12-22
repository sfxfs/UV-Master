#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "s2j.h"
#include "cJSON.h"

#include "uvm-cfg.h"

#define CONFIG_FILE_PATH "config.json"

static void uvm_cfg_initialize_value(config_data data_s)
{
    data_s.dev_ctl = dev_ctl_create_with_init_val();
    data_s.propeller = propeller_create_with_init_val();
    data_s.rocket_ratio = rocket_ratio_create_with_init_val();
    data_s.others = others_create_with_init_val();
}

void uvm_cfg_free (config_data data_s)
{
    if (data_s.dev_ctl)
        free(data_s.dev_ctl);
    if (data_s.propeller)
        free(data_s.propeller);
    if (data_s.rocket_ratio)
        free(data_s.rocket_ratio);
    if (data_s.others)
        free(data_s.others);
}

config_data uvm_cfg_read ()
{

}

config_data uvm_cfg_init ()
{
    config_data config = {0};

    if (0 == access(CONFIG_FILE_PATH, F_OK)) // 0:存在
    {
        config = uvm_cfg_read();
    }
    else
    {
        uvm_cfg_initialize_value(config); //初始化Rov_info
        if (uvm_cfg_write(config) < 0) //创建并将Rov_info信息写至config
        {
            printf("config write error...");
        }
    }
    return config;
}
