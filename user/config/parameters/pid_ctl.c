//
// Created by fxf on 23-9-4.
//

#include "pid_ctl.h"

/**
 * @brief 单个pid控制系统参数添加（Creat Json and Add Param）
 * @param params pid_scale_parameters结构体参数
 * @return Json对象
 */
cJSON* pid_ctl_params_add_to_root(struct pid_scale_parameters *params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddNumberToObject(node, "p", params->Kp);
    cJSON_AddNumberToObject(node, "i", params->Ki);
    cJSON_AddNumberToObject(node, "d", params->Kd);

    return node;
}

/**
 * @brief 单个pid控制系统参数读取（from Json）
 * @param params pid_scale_parameters结构体参数
 * @param node Json对象
 */
void pid_ctl_params_read_from_root(struct pid_scale_parameters *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->Kp = (float)cJSON_GetObjectItem(node, "p")->valuedouble;
    params->Ki = (float)cJSON_GetObjectItem(node, "i")->valuedouble;
    params->Kd = (float)cJSON_GetObjectItem(node, "d")->valuedouble;
}

/**
 * @brief 单个pid控制系统参数初始化
 * @param params pid_scale_parameters结构体参数
 */
void pid_ctl_params_init(struct pid_scale_parameters *params)
{
    params->Kp = 0.1f;
    params->Ki = 0;
    params->Kd = 0;
}
