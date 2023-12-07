#include <unistd.h>
#include <string.h>
#include "s2j.h"
#include "cJSON.h"

#include "uvm-cfg.h"

#define CONFIG_FILE_PATH "config.json"

static void uvm_cfg_initialize_value(struct config_data *data_s)
{

}

int uvm_cfg_init(struct config_data *data_s)
{
    bzero(data_s, sizeof(struct config_data));

    if (0 == access(CONFIG_FILE_PATH, F_OK)) // 0:存在
    {
        if (uvm_cfg_read(data_s) < 0)  //能够读取则不做任何事
        {
            return -1;
        }
    }
    else
    {
        uvm_cfg_initialize_value(data_s); //初始化Rov_info
        if (uvm_cfg_write(data_s) < 0) //创建并将Rov_info信息写至config
        {
            return -1;
        }
    }
    return 0;
}
