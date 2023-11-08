//
// Created by fxf on 9/25/23.
//
#include "utils.h"

#include "rocket_ratio.h"

/**
 * @brief 单个推进器比率参数添加（Creat Json and Add Param）
 * @param params power_dir结构体参数
 * @return Json对象
 */
static cJSON* _rocket_dir_add_to_root(rocket_propeller_attr_t params)
{
    cJSON* node = cJSON_CreateObject();
    if (node == NULL)
        return NULL;

    cJSON_AddBoolToObject(node, "reversed", params.reversed);
    cJSON_AddNumberToObject(node, "ratio_p", params.ratio_p);
    cJSON_AddNumberToObject(node, "ratio_n", params.ratio_n);

    return node;
}

/**
 * @brief 单个推进器比率读取（From Json）
 * @param params power_dir结构体参数
 * @param node Json对象
 */
static void _rocket_dir_read_from_root(rocket_propeller_attr_t *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->reversed = cjson_value_analysis_int(node, "reversed");
    params->ratio_p = cjson_value_analysis_double(node, "ratio_p");
    params->ratio_n = cjson_value_analysis_double(node, "ratio_n");
}

/**
 * @brief 单个推进器比率初始化（默认0.5倍）
 * @param params power_dir结构体参数
 */
static void _rocket_dir_params_init(rocket_propeller_attr_t *params)
{
    params->reversed = false;
    params->ratio_p = 0.15;
    params->ratio_n = 0.15;
}

/**
 * @brief 推进器比率参数添加（Creat Json and Add Param）
 * @param params r2p_ratio结构体参数
 * @return Json对象
 */
cJSON* rocket_ratio_params_add_to_root(rocket_axis_attr_t *params)
{
    cJSON* node = cJSON_CreateObject();
    if (node == NULL)
        return NULL;

    cJSON_AddItemToObject(node, "front_right", _rocket_dir_add_to_root(params->front_right));
    cJSON_AddItemToObject(node, "front_left", _rocket_dir_add_to_root(params->front_left));
    cJSON_AddItemToObject(node, "center_right", _rocket_dir_add_to_root(params->center_right));
    cJSON_AddItemToObject(node, "center_left", _rocket_dir_add_to_root(params->center_left));
    cJSON_AddItemToObject(node, "back_right", _rocket_dir_add_to_root(params->back_right));
    cJSON_AddItemToObject(node, "back_left", _rocket_dir_add_to_root(params->back_left));

    return node;
}

/**
 * @brief 推进器比率读取（From Json）
 * @param params r2p_ratio结构体参数
 * @param node Json对象
 */
void rocket_ratio_params_read_from_root(rocket_axis_attr_t *params, cJSON *node)
{
    if (node == NULL)
        return;
    _rocket_dir_read_from_root(&params->front_right, cJSON_GetObjectItem(node, "front_right"));
    _rocket_dir_read_from_root(&params->front_left, cJSON_GetObjectItem(node, "front_left"));
    _rocket_dir_read_from_root(&params->center_right, cJSON_GetObjectItem(node, "center_right"));
    _rocket_dir_read_from_root(&params->center_left, cJSON_GetObjectItem(node, "center_left"));
    _rocket_dir_read_from_root(&params->back_right, cJSON_GetObjectItem(node, "back_right"));
    _rocket_dir_read_from_root(&params->back_left, cJSON_GetObjectItem(node, "back_left"));
}

/**
 * @brief 推进器比率初始化（默认0.5倍）
 * @param params r2p_ratio结构体参数
 */
void rocket_ratio_params_init(rocket_axis_attr_t *params)
{
    _rocket_dir_params_init(&params->front_right);
    _rocket_dir_params_init(&params->front_left);
    _rocket_dir_params_init(&params->center_right);
    _rocket_dir_params_init(&params->center_left);
    _rocket_dir_params_init(&params->back_right);
    _rocket_dir_params_init(&params->back_left);
}

void rocket_ratio_params_all_init(rocket_t *params)
{
    rocket_ratio_params_init(&params->L_UD);
    rocket_ratio_params_init(&params->L_LR);
    rocket_ratio_params_init(&params->R_UD);
    rocket_ratio_params_init(&params->R_LR);
}

/**
 * @brief 各轴参数写入（Creat Json and Add params）
 * @param info rov_info结构体参数
 * @return Json对象
 */
cJSON* rocket_ratio_params_write(struct rov_info* info)
{
    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
        return NULL;

    cJSON_AddItemToObject(root, "L_UD", rocket_ratio_params_add_to_root(&info->rocket.L_UD));
    cJSON_AddItemToObject(root, "L_LR", rocket_ratio_params_add_to_root(&info->rocket.L_LR));
    cJSON_AddItemToObject(root, "R_UD", rocket_ratio_params_add_to_root(&info->rocket.R_UD));
    cJSON_AddItemToObject(root, "R_LR", rocket_ratio_params_add_to_root(&info->rocket.R_LR));

    return root;
}

/**
 * @brief 各轴推进器参数读取（From Json）
 * @param info rov_info结构体参数
 * @param node Json对象
 */
void rocket_ratio_params_read(struct rov_info* info, cJSON *node)
{
    if (node == NULL)
        return;
    rocket_ratio_params_read_from_root(&info->rocket.L_UD, cJSON_GetObjectItem(node, "L_UD"));
    rocket_ratio_params_read_from_root(&info->rocket.L_LR, cJSON_GetObjectItem(node, "L_LR"));
    rocket_ratio_params_read_from_root(&info->rocket.R_UD, cJSON_GetObjectItem(node, "R_UD"));
    rocket_ratio_params_read_from_root(&info->rocket.R_LR, cJSON_GetObjectItem(node, "R_LR"));
}
