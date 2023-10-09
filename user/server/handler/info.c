#include <stdio.h>
#include <stdlib.h>
#include "data_define.h"

#include "info.h"

static cJSON *get_rov_info(sensor_t *sensor_data)
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

static cJSON *get_rov_debug_info(debug_info_t *info)
{
    cJSON* cjson_pid_feedbacks = cJSON_CreateObject();
    cJSON* cjson_pid_control_loops = cJSON_CreateObject();

    cJSON_AddNumberToObject(cjson_pid_control_loops, "depth_lock", info->depth_diffen);
    cJSON_AddNumberToObject(cjson_pid_control_loops, "direction_lock", info->yaw_diffen);
    cJSON_AddItemToObject(cjson_pid_feedbacks, "control_loops", cjson_pid_control_loops);

    return cjson_pid_feedbacks;
}

cJSON *info_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return get_rov_info(ctx->data);
}

cJSON *debug_info_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return get_rov_debug_info(ctx->data);
}

cJSON *update_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    // to do ...
    return cJSON_CreateNull();
}
