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
cJSON* dev_ctl_params_add_to_root(struct pwmDev_parameters *params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddNumberToObject(node, "channel", params->channel);
    cJSON_AddNumberToObject(node, "pMax", params->pMax);
    cJSON_AddNumberToObject(node, "nMax", params->nMax);
    cJSON_AddNumberToObject(node, "reset", params->reset);
    cJSON_AddNumberToObject(node, "speed", params->speed);

    return node;
}

/**
 * @brief 单个pwm设备参数读取（from Json）
 * @param params pwmDev_parameters结构体参数
 * @param node Json对象
 */
void dev_ctl_params_read_from_root(struct pwmDev_parameters *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->channel = cjson_value_analysis_int(node, "channel");
    params->pMax = cjson_value_analysis_int(node, "pMax");
    params->nMax = cjson_value_analysis_int(node, "nMax");
    params->reset = cjson_value_analysis_int(node, "reset");
    params->speed = cjson_value_analysis_int(node, "speed");
}

/**
 * @brief 单个PWM设备参数初始化
 * @param params pwmDev_parameters结构体参数
 */
void dev_ctl_params_init(struct pwmDev_parameters *params)
{
    params->channel = 0;
    params->pMax = 1000;
    params->nMax = 0;
    params->reset = 500;
    params->speed = 50;
}

void dev_ctl_params_all_init(dev_ctl_t *params)
{
    dev_ctl_params_init(&params->light);
    dev_ctl_params_init(&params->yuntai);
    dev_ctl_params_init(&params->arm);
}

/**
 * @brief pwm设备参数添加(Creat Json and Add param)
 * @param info rov_info结构体参数
 * @return Json对象
 */
cJSON* dev_ctl_params_write(struct rov_info* info)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "light", dev_ctl_params_add_to_root(&info->devCtl.light));
    cJSON_AddItemToObject(root, "yuntai", dev_ctl_params_add_to_root(&info->devCtl.yuntai));
    cJSON_AddItemToObject(root, "arm", dev_ctl_params_add_to_root(&info->devCtl.arm));

    return root;
}

/**
 * @brief pwm设备参数读取（From Json）
 * @param info rov_info结构体参数
 * @param node Json对象
 */
void dev_ctl_params_read(struct rov_info* info, cJSON *node)
{
    if (node == NULL)
        return;
    dev_ctl_params_read_from_root(&info->devCtl.arm, cJSON_GetObjectItem(node, "arm"));
    dev_ctl_params_read_from_root(&info->devCtl.light, cJSON_GetObjectItem(node, "light"));
    dev_ctl_params_read_from_root(&info->devCtl.yuntai, cJSON_GetObjectItem(node, "yuntai"));
}
