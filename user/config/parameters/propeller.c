//
// Created by fxf on 23-9-4.
//

#include "propeller.h"

/**
 * @brief 单个推进器参数添加（Creat Json and Add Param）
 * @param params propeller_parameters结构体参数
 * @return Json对象
 */
cJSON* propeller_params_add_to_root(struct propeller_parameters *params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddItemToObject(node, "reversed", params->reversed == 1 ? cJSON_CreateTrue() : cJSON_CreateFalse());
    cJSON_AddItemToObject(node, "enabled", params->enabled == 1 ? cJSON_CreateTrue() : cJSON_CreateFalse());
    cJSON_AddNumberToObject(node, "channel", params->channel);
    cJSON_AddNumberToObject(node, "deadzone_lower", params->deadzone_lower);
    cJSON_AddNumberToObject(node, "deadzone_upper", params->deadzone_upper);
    cJSON_AddNumberToObject(node, "power_positive", params->power_positive);
    cJSON_AddNumberToObject(node, "power_negative", params->power_negative);

    return node;
}

/**
 * @brief 单个推进器参数读取（from Json）
 * @param params propeller_parameters结构体参数
 * @param node Json对象
 */
void propeller_params_read_from_root(struct propeller_parameters *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->reversed =  cJSON_GetObjectItem(node, "reversed")->valueint;
    params->enabled =  cJSON_GetObjectItem(node, "enabled")->valueint;
    params->channel = cJSON_GetObjectItem(node, "channel")->valueint;
    params->power_positive = cJSON_GetObjectItem(node, "power_positive")->valuedouble;
    params->power_negative = cJSON_GetObjectItem(node, "power_negative")->valuedouble;
    params->deadzone_upper = cJSON_GetObjectItem(node, "deadzone_upper")->valueint;
    params->deadzone_lower = cJSON_GetObjectItem(node, "deadzone_lower")->valueint;
}

/**
 * @brief 单个推进器频率初始化（默认50 HZ ）
 * @param params 推进器PWM频率参数（propeller.pwm_freq_calibration）
 */
void propeller_params_init_freq(double *params)
{
    *params = 50;
}

/**
 * @brief 单个推进器参数初始化
 * @param params propeller_parameters结构体参数
 */
void propeller_params_init(struct propeller_parameters *params)
{
    params->enabled = 1;
    params->reversed = 0;
    params->channel = 0;
    params->deadzone_upper = 0;
    params->deadzone_lower = 0;
    params->power_positive = 0.2;
    params->power_negative = 0.2;
}
