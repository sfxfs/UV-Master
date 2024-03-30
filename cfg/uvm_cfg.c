#include "uvm_cfg.h"

#include "log.h"
#include "cJSON.h"
#include "uvm_cfg_intf.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int uvm_cfg_initialize_value(config_data data_s)
{
    uvm_cfg_delete(data_s);
    data_s.dev_ctl = dev_ctl_create_with_init_val();
    data_s.propeller = propeller_create_with_init_val();
    data_s.rocket_ratio = rocket_ratio_create_with_init_val();
    data_s.others = others_create_with_init_val();

    if (data_s.dev_ctl && data_s.propeller && data_s.rocket_ratio && data_s.others)
        return 0;
    return -1;
}

void uvm_cfg_delete(config_data data_s)
{
    if (data_s.dev_ctl)
        free(data_s.dev_ctl);
    if (data_s.propeller)
        free(data_s.propeller);
    if (data_s.rocket_ratio)
        free(data_s.rocket_ratio);
    if (data_s.others)
        free(data_s.others);
    bzero(&data_s, sizeof(config_data));
}

int uvm_cfg_read (config_data data_s)
{
    uvm_cfg_delete(data_s);

    char *data = uvm_intf_read_from_file();
    if (data == NULL)
    {
        return -1;
    }
    cJSON *json = cJSON_Parse(data);
    free(data);
    if (json == NULL)
    {
        return -2;
    }

    data_s.others = others_j2s(cJSON_GetObjectItem(json, "others_params"));
    data_s.dev_ctl = dev_ctl_j2s(cJSON_GetObjectItem(json, "dev_ctl_params"));
    data_s.propeller = propeller_j2s(cJSON_GetObjectItem(json, "propeller_params"));
    data_s.rocket_ratio = rocket_ratio_j2s(cJSON_GetObjectItem(json, "rocket_ratio_params"));

    cJSON_Delete(json);

    if (data_s.dev_ctl && data_s.propeller && data_s.rocket_ratio && data_s.others)
    {
        log_info("Config file read succeed.");
        return 0;
    }
    return -1;
}



int uvm_cfg_write(config_data data_s)
{
    void *temp = NULL;
    cJSON *json = cJSON_CreateObject();

    if (data_s.others)
        cJSON_AddItemToObject(json, "others_params", others_s2j(data_s.others));
    else
    {
        temp = others_create_with_init_val();
        cJSON_AddItemToObject(json, "others_params", others_s2j(temp));
        free(temp);
    }

    if (data_s.dev_ctl)
        cJSON_AddItemToObject(json, "dev_ctl_params", dev_ctl_s2j(data_s.dev_ctl));
    else
    {
        temp = dev_ctl_create_with_init_val();
        cJSON_AddItemToObject(json, "dev_ctl_params", others_s2j(temp));
        free(temp);
    }

    if (data_s.propeller)
        cJSON_AddItemToObject(json, "propeller_params", propeller_s2j(data_s.propeller));
    else
    {
        temp = propeller_create_with_init_val();
        cJSON_AddItemToObject(json, "propeller_params", others_s2j(temp));
        free(temp);
    }

    if (data_s.rocket_ratio)
        cJSON_AddItemToObject(json, "rocket_ratio_params", rocket_ratio_s2j(data_s.rocket_ratio));
    else
    {
        temp = rocket_ratio_create_with_init_val();
        cJSON_AddItemToObject(json, "rocket_ratio_params", others_s2j(temp));
        free(temp);
    }

    char *str = cJSON_Print(json);
    cJSON_Delete(json);

    int ret = uvm_intf_write_to_file(str);
    free(str);

    return ret;
}

int uvm_cfg_init(config_data data_s)
{
    if (0 == access(CONFIG_FILE_PATH, F_OK)) // 0:存在
    {
        return uvm_cfg_read(data_s);
    }

    if (uvm_cfg_initialize_value(data_s) != 0) // 初始化Rov_info
    {
        log_error("Config set initial value error.");
        return -1;
    }

    if (uvm_cfg_write(data_s) < 0)    // 创建并将Rov_info信息写至config
    {
        log_error("Config file write error.");
        return -2;
    }

    log_info("Config file write succeed.");
    return 0;
}
