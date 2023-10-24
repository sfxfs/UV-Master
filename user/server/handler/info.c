#include <stdio.h>
#include <stdlib.h>
#include "data_define.h"

#include "info.h"

/**
 * @brief 获取rov温度及位置信息（from sensor_t to Cjson）
 * @param sensor_data sensor_t结构体参数
 * @return cjson
 */
static cJSON *get_rov_info(sensorDev_info_t *sensor_data)
{
    cJSON* cjson_info = NULL;
    cjson_info = cJSON_CreateObject();
    char *temp_str = malloc(sizeof(char) * 20);
    if (sensor_data->temperature != 0.0f)
    {
        sprintf(temp_str, "%.02f ℃", sensor_data->temperature);
        cJSON_AddStringToObject(cjson_info, "温度", temp_str);
    }
    if (sensor_data->yaw != 0.0f)
    {
        sprintf(temp_str, "%.02f °", sensor_data->yaw);
        cJSON_AddStringToObject(cjson_info, "航向角", temp_str);
    }
    if (sensor_data->depth > 0.0f)
    {
        sprintf(temp_str, "%.02f cm", sensor_data->depth);
        cJSON_AddStringToObject(cjson_info, "深度", temp_str);
    }
    free(temp_str);
    return cjson_info;
}

/**
 * @brief 链接get_rov_info函数
 * @param ctx 下位机info->sensor的指针
 * @return Cjson object
 */
cJSON *info_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return get_rov_info(ctx->data);
}

/**
 * @brief 链接get_rov_debug_info函数
 * @param ctx 下位机调试状态信息
 * @return Cjson object
 */
cJSON *debug_info_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return cJSON_CreateNull();
}

/**
 * @brief Add anything you want to do 
 * @param ctx 
 * @param params 
 * @param id 
 * @return Cjson NUll
 */
cJSON *update_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    // to do ...
    return cJSON_CreateNull();
}
