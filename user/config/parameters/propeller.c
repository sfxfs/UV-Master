//
// Created by fxf on 23-9-4.
//
#include "utils.h"

#include "propeller.h"

/**
 * @brief 单个推进器参数添加（Creat Json and Add Param）
 * @param params propeller_parameters结构体参数
 * @return Json对象
 */
cJSON* propeller_params_add_to_root(propeller_attr_t *params)
{
    cJSON* node = cJSON_CreateObject();
    if (node == NULL)
        return NULL;

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
 * @brief 推进器频率读取（from Cjson）
 * @param freq propeller.pwm_freq_calibration
 * @param node Cjson
 */
void propeller_freq_read_from_root(uint16_t *freq, cJSON *node)
{
    if (node == NULL)
        return;
    *freq = node->valueint;
}

/**
 * @brief 单个推进器参数读取（from Json）
 * @param params propeller_parameters结构体参数
 * @param node Json对象
 */
void propeller_params_read_from_root(propeller_attr_t *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->reversed =  cjson_value_analysis_int(node, "reversed");
    params->enabled =  cjson_value_analysis_int(node, "enabled");
    params->channel = cjson_value_analysis_int(node, "channel");
    params->power_positive = cjson_value_analysis_double(node, "power_positive");
    params->power_negative = cjson_value_analysis_double(node, "power_negative");
    params->deadzone_upper = cjson_value_analysis_int(node, "deadzone_upper");
    params->deadzone_lower = cjson_value_analysis_int(node, "deadzone_lower");
}

/**
 * @brief 单个推进器频率初始化（默认50 HZ ）
 * @param params 推进器PWM频率参数（propeller.pwm_freq_calibration）
 */
void propeller_params_init_freq(uint16_t *params)
{
    *params = 50;
}

/**
 * @brief 单个推进器参数初始化
 * @param params propeller_parameters结构体参数
 */
void propeller_params_init(propeller_attr_t *params)
{
    params->enabled = 1;
    params->reversed = 0;
    params->channel = 0;
    params->deadzone_upper = 25;
    params->deadzone_lower = -25;
    params->power_positive = 0.4;
    params->power_negative = 0.4;
}

void propeller_params_all_init(propeller_t *params)
{
    propeller_params_init_freq(&params->pwm_freq_calibration);
    propeller_params_init(&params->front_right);
    propeller_params_init(&params->front_left);
    propeller_params_init(&params->center_right);
    propeller_params_init(&params->center_left);
    propeller_params_init(&params->back_right);
    propeller_params_init(&params->back_left);
}

/**
 * @brief 推进器参数添加（Creat Json and Add params）
 * @param info rov_info结构体参数
 * @return Json对象
 */
cJSON* propeller_params_write(struct rov_info* info)
{
    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
        return NULL;

    cJSON_AddNumberToObject(root, "pwm_freq_calibration", info->propeller.pwm_freq_calibration);
    cJSON_AddItemToObject(root, "front_right", propeller_params_add_to_root(&info->propeller.front_right));
    cJSON_AddItemToObject(root, "front_left", propeller_params_add_to_root(&info->propeller.front_left));
    cJSON_AddItemToObject(root, "center_right", propeller_params_add_to_root(&info->propeller.center_right));
    cJSON_AddItemToObject(root, "center_left", propeller_params_add_to_root(&info->propeller.center_left));
    cJSON_AddItemToObject(root, "back_right", propeller_params_add_to_root(&info->propeller.back_right));
    cJSON_AddItemToObject(root, "back_left", propeller_params_add_to_root(&info->propeller.back_left));

    return root;
}

/**
 * @brief 推进器参数读取（From Json）
 * @param info rov_info结构体参数
 * @param node Json对象
 */
void propeller_params_read(struct rov_info* info, cJSON *node)
{
    if (node == NULL)
        return;
    propeller_freq_read_from_root(&info->propeller.pwm_freq_calibration, cJSON_GetObjectItem(node, "pwm_freq_calibration"));
    propeller_params_read_from_root(&info->propeller.front_right, cJSON_GetObjectItem(node, "front_right"));
    propeller_params_read_from_root(&info->propeller.front_left, cJSON_GetObjectItem(node, "front_left"));
    propeller_params_read_from_root(&info->propeller.center_right, cJSON_GetObjectItem(node, "center_right"));
    propeller_params_read_from_root(&info->propeller.center_left, cJSON_GetObjectItem(node, "center_left"));
    propeller_params_read_from_root(&info->propeller.back_right, cJSON_GetObjectItem(node, "back_right"));
    propeller_params_read_from_root(&info->propeller.back_left, cJSON_GetObjectItem(node, "back_left"));
}
