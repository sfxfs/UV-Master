//
// Created by fxf on 9/25/23.
//

#include "utils.h"

#include "rocket_ratio.h"

static const char ra_temp[ROCKET_AXIS_NUM][5] = {
    "ra_x",
    "ra_y",
    "ra_z",
    "ra_r"
    };

static const char pp_temp[PROPELLER_NUM][13] = {
    "front_right",
    "front_left",
    "center_right",
    "center_left",
    "back_right",
    "back_left"
    };

/**
 * @brief 单个推进器比率参数添加（Creat Json and Add Param）
 * @param params power_dir结构体参数
 * @return Json对象
 */
cJSON* rocket_ratio_params_add_to_root(struct rocket_ratio_attr *params)
{
    cJSON* node = cJSON_CreateObject();
    if (node == NULL)
        return NULL;

    cJSON_AddBoolToObject(node, "enabled", params->enabled);
    cJSON_AddBoolToObject(node, "reversed", params->reversed);
    cJSON_AddNumberToObject(node, "ratio_p", params->ratio_p);
    cJSON_AddNumberToObject(node, "ratio_n", params->ratio_n);

    return node;
}

/**
 * @brief 单个推进器比率读取（From Json）
 * @param params power_dir结构体参数
 * @param node Json对象
 */
void rocket_ratio_params_read_from_root(struct rocket_ratio_attr *params, cJSON *node)
{
    if (node == NULL)
        return;

    params->enabled = cjson_value_analysis_int(node, "enabled");
    params->reversed = cjson_value_analysis_int(node, "reversed");
    params->ratio_p = cjson_value_analysis_double(node, "ratio_p");
    params->ratio_n = cjson_value_analysis_double(node, "ratio_n");
}

/**
 * @brief 单个推进器比率初始化（默认0.5倍）
 * @param params power_dir结构体参数
 */
void rocket_ratio_params_init(struct rocket_ratio_attr *params)
{
    params->enabled = true;
    params->reversed = false;
    params->ratio_p = 0.15;
    params->ratio_n = 0.15;
}

void rocket_ratio_params_all_init(struct rocket_ratio_params *params)
{
    for (size_t i = 0; i < ROCKET_AXIS_NUM; i++)
        for (size_t j = 0; j < PROPELLER_NUM; j++)
            rocket_ratio_params_init(&params->attr[i][j]);
}

/**
 * @brief 各轴参数写入（Creat Json and Add params）
 * @param info rov_info结构体参数
 * @return Json对象
 */
cJSON* rocket_ratio_params_write(struct rocket_ratio_params *params)
{
    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
        return NULL;

    cJSON *per_axis = NULL;
    for (size_t i = 0; i < ROCKET_AXIS_NUM; i++)
    {
        for (size_t j = 0; j < PROPELLER_NUM; j++)
        {
            per_axis = cJSON_CreateObject();
            cJSON_AddItemToObject(per_axis, pp_temp[j], rocket_ratio_params_add_to_root(&params->attr[i][j]));
        }
        cJSON_AddItemToObject(root, ra_temp[i], per_axis);
    }

    return root;
}

/**
 * @brief 各轴推进器参数读取（From Json）
 * @param info rov_info结构体参数
 * @param node Json对象
 */
void rocket_ratio_params_read(struct rocket_ratio_params *params, cJSON *node)
{
    if (node == NULL)
        return;

    cJSON *per_axis = NULL;
    for (size_t i = 0; i < ROCKET_AXIS_NUM; i++)
    {
        per_axis = cJSON_GetObjectItem(node, ra_temp[i]);
        for (size_t j = 0; j < PROPELLER_NUM; j++)
        {
            rocket_ratio_params_read_from_root(&params->attr[i][j], cJSON_GetObjectItem(per_axis, pp_temp[j]));
        }
    }
}
