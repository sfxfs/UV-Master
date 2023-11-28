//
// Created by fxf on 23-9-4.
//

#include "utils.h"

#include "dev_ctl.h"

/**
 * @brief 单个pwm设备参数添加（Creat Json and Add Param）
 * @param params pwmDev_parameters结构体参数
 * @return Json对象
 */
cJSON* dev_ctl_params_add_to_root(struct dev_ctl_attr *params)
{
    cJSON* node = cJSON_CreateObject();
    if (node == NULL)
        return NULL;

    cJSON_AddBoolToObject(node, "enabled", params->enabled);
    cJSON_AddNumberToObject(node, "channel", params->channel);
    cJSON_AddNumberToObject(node, "pMax", params->pMax);
    cJSON_AddNumberToObject(node, "nMax", params->nMax);
    cJSON_AddNumberToObject(node, "reset", params->reset);
    cJSON_AddNumberToObject(node, "step", params->step);

    return node;
}

/**
 * @brief 单个pwm设备参数读取（from Json）
 * @param params pwmDev_parameters结构体参数
 * @param node Json对象
 */
void dev_ctl_params_read_from_root(struct dev_ctl_attr *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->enabled = cjson_value_analysis_int(node, "enabled");
    params->channel = cjson_value_analysis_int(node, "channel");
    params->pMax = cjson_value_analysis_int(node, "pMax");
    params->nMax = cjson_value_analysis_int(node, "nMax");
    params->reset = cjson_value_analysis_int(node, "reset");
    params->step = cjson_value_analysis_int(node, "step");
}

/**
 * @brief 单个PWM设备参数初始化
 * @param params pwmDev_parameters结构体参数
 */
void dev_ctl_params_init(struct dev_ctl_attr *params)
{
    params->enabled = false;
    params->channel = 0;
    params->pMax = 1000;
    params->nMax = 0;
    params->reset = 500;
    params->step = 50;
}

/**
 * @brief 所有PWM设备参数初始化
 * @param params 结构体参数
 */
void dev_ctl_params_all_init(struct dev_ctl_params *params)
{
    for (size_t i = 0; i < DEV_NUM; i++)
        dev_ctl_params_init(&params->attr[i]);
}

/**
 * @brief pwm设备参数添加(Creat Json and Add param)
 * @param info rov_info结构体参数
 * @return Json对象
 */
cJSON* dev_ctl_params_write(struct dev_ctl_params *params)
{
    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
        return NULL;

    cJSON_AddItemToObject(root, "arm", dev_ctl_params_add_to_root(&params->attr[DEV_CTL_ARM]));
    cJSON_AddItemToObject(root, "light", dev_ctl_params_add_to_root(&params->attr[DEV_CTL_LIGHT]));

    return root;
}

/**
 * @brief pwm设备参数读取（From Json）
 * @param info rov_info结构体参数
 * @param node Json对象
 */
void dev_ctl_params_read(struct dev_ctl_params *params, cJSON *node)
{
    if (node == NULL)
        return;
    dev_ctl_params_read_from_root(&params->attr[DEV_CTL_ARM], cJSON_GetObjectItem(node, "arm"));
    dev_ctl_params_read_from_root(&params->attr[DEV_CTL_LIGHT], cJSON_GetObjectItem(node, "light"));
}
