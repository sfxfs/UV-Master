//
// Created by fxf on 23-9-4.
//

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
    params->channel = cJSON_GetObjectItem(node, "channel")->valueint;
    params->pMax = cJSON_GetObjectItem(node, "pMax")->valueint;
    params->nMax = cJSON_GetObjectItem(node, "nMax")->valueint;
    params->reset = cJSON_GetObjectItem(node, "reset")->valueint;
    params->speed = cJSON_GetObjectItem(node, "speed")->valueint;
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
