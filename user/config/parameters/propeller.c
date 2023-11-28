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
cJSON* propeller_params_add_to_root(struct propeller_attr *params)
{
    cJSON* node = cJSON_CreateObject();
    if (node == NULL)
        return NULL;

    cJSON_AddBoolToObject(node, "reversed", params->reversed);
    cJSON_AddBoolToObject(node, "enabled", params->enabled);
    cJSON_AddNumberToObject(node, "channel", params->channel);
    cJSON_AddNumberToObject(node, "deadzone_upper", params->deadzone_upper);
    cJSON_AddNumberToObject(node, "deadzone_lower", params->deadzone_lower);
    cJSON_AddNumberToObject(node, "power_positive", params->power_positive);
    cJSON_AddNumberToObject(node, "power_negative", params->power_negative);

    return node;
}

/**
 * @brief 单个推进器参数读取（from Json）
 * @param params propeller_parameters结构体参数
 * @param node Json对象
 */
void propeller_params_read_from_root(struct propeller_attr *params, cJSON *node)
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
 * @brief 单个推进器参数初始化
 * @param params propeller_attr_t 结构体参数
 */
void propeller_params_init(struct propeller_attr *params)
{
    params->enabled = true;
    params->reversed = false;
    params->channel = 0;
    params->deadzone_upper = 25;
    params->deadzone_lower = -25;
    params->power_positive = 0.4;
    params->power_negative = 0.4;
}

/**
 * @brief 所有推进器参数初始化
 * @param params propeller_attr_t 结构体参数
 */
void propeller_params_all_init(struct propeller_params *params)
{
    for (size_t i = 0; i < PROPELLER_NUM; i++)
        propeller_params_init(&params->attr[i]);
}

/**
 * @brief 推进器参数添加（Creat Json and Add params）
 * @param info rov_info结构体参数
 * @return Json对象
 */
cJSON* propeller_params_write(struct propeller_params *params)
{
    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
        return NULL;
    int which = PP_FRONT_RIGHT;

    cJSON_AddNumberToObject(root, "pwm_freq_calibration", params->pwm_freq_offset);
    cJSON_AddItemToObject(root, "front_right", propeller_params_add_to_root(&params->attr[which++]));
    cJSON_AddItemToObject(root, "front_left", propeller_params_add_to_root(&params->attr[which++]));
    cJSON_AddItemToObject(root, "center_right", propeller_params_add_to_root(&params->attr[which++]));
    cJSON_AddItemToObject(root, "center_left", propeller_params_add_to_root(&params->attr[which++]));
    cJSON_AddItemToObject(root, "back_right", propeller_params_add_to_root(&params->attr[which++]));
    cJSON_AddItemToObject(root, "back_left", propeller_params_add_to_root(&params->attr[which++]));

    return root;
}

/**
 * @brief 推进器参数读取（From Json）
 * @param info rov_info结构体参数
 * @param node Json对象
 */
void propeller_params_read(struct propeller_params *params, cJSON *node)
{
    if (node == NULL)
        return;
    int which = PP_FRONT_RIGHT;

    params->pwm_freq_offset = cjson_value_analysis_int(node, "pwm_freq_calibration");
    propeller_params_read_from_root(&params->attr[which++], cJSON_GetObjectItem(node, "front_right"));
    propeller_params_read_from_root(&params->attr[which++], cJSON_GetObjectItem(node, "front_left"));
    propeller_params_read_from_root(&params->attr[which++], cJSON_GetObjectItem(node, "center_right"));
    propeller_params_read_from_root(&params->attr[which++], cJSON_GetObjectItem(node, "center_left"));
    propeller_params_read_from_root(&params->attr[which++], cJSON_GetObjectItem(node, "back_right"));
    propeller_params_read_from_root(&params->attr[which++], cJSON_GetObjectItem(node, "back_left"));
}
