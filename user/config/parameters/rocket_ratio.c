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
static cJSON* _rocket_dir_add_to_root(struct power_dir params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddItemToObject(node, "reversed", params.reversed == 1 ? cJSON_CreateTrue() : cJSON_CreateFalse());
    cJSON_AddNumberToObject(node, "p", params.p);
    cJSON_AddNumberToObject(node, "n", params.n);

    return node;
}

/**
 * @brief 单个推进器比率读取（From Json）
 * @param params power_dir结构体参数
 * @param node Json对象
 */
static void _rocket_dir_read_from_root(struct power_dir *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->reversed = cjson_value_analysis_int(node, "reversed");
    params->p = cjson_value_analysis_double(node, "p");
    params->n = cjson_value_analysis_double(node, "n");
}

/**
 * @brief 单个推进器比率初始化（默认0.5倍）
 * @param params power_dir结构体参数
 */
static void _rocket_dir_params_init(struct power_dir *params)
{
    params->reversed = false;
    params->p = 0.5;
    params->n = 0.5;
}

/**
 * @brief 推进器比率参数添加（Creat Json and Add Param）
 * @param params r2p_ratio结构体参数
 * @return Json对象
 */
cJSON* rocket_ratio_params_add_to_root(struct r2p_ratio *params)
{
    cJSON* node = cJSON_CreateObject();

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
void rocket_ratio_params_read_from_root(struct r2p_ratio *params, cJSON *node)
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
void rocket_ratio_params_init(struct r2p_ratio *params)
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
    rocket_ratio_params_init(&params->ratio_x);
    rocket_ratio_params_init(&params->ratio_y);
    rocket_ratio_params_init(&params->ratio_z);
    rocket_ratio_params_init(&params->ratio_yaw);
}

/**
 * @brief 各轴参数写入（Creat Json and Add params）
 * @param info rov_info结构体参数
 * @return Json对象
 */
cJSON* rocket_ratio_params_write(struct rov_info* info)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "rx", rocket_ratio_params_add_to_root(&info->rocket.ratio_x));
    cJSON_AddItemToObject(root, "ry", rocket_ratio_params_add_to_root(&info->rocket.ratio_y));
    cJSON_AddItemToObject(root, "rz", rocket_ratio_params_add_to_root(&info->rocket.ratio_z));
    cJSON_AddItemToObject(root, "ryaw", rocket_ratio_params_add_to_root(&info->rocket.ratio_yaw));

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
    rocket_ratio_params_read_from_root(&info->rocket.ratio_x, cJSON_GetObjectItem(node, "rx"));
    rocket_ratio_params_read_from_root(&info->rocket.ratio_y, cJSON_GetObjectItem(node, "ry"));
    rocket_ratio_params_read_from_root(&info->rocket.ratio_z, cJSON_GetObjectItem(node, "rz"));
    rocket_ratio_params_read_from_root(&info->rocket.ratio_yaw, cJSON_GetObjectItem(node, "ryaw"));
}
