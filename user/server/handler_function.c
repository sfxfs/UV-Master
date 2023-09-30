//
// Created by fxf on 23-7-9.
//

#include <stdio.h>
#include <stdlib.h>

#include "handler_function.h"

int cjson_value_analysis_int(cJSON *params, const char *str)
{
    cJSON* cjson_temp = NULL;
    int value;
    cjson_temp = cJSON_GetObjectItem(params, str);
    if (cjson_temp != NULL)      //如果没收到则返回
    {
        value = cjson_temp->valueint;
    }
    else value = 0;
    return value;
}

double cjson_value_analysis_double(cJSON *params,const char *str)
{
    cJSON* cjson_temp = NULL;
    double value;
    cjson_temp = cJSON_GetObjectItem(params, str);
    if (cjson_temp != NULL)      //如果没收到则返回
    {
        value = cjson_temp->valuedouble;
    }
    else value = 0;
    return value;
}

cJSON *get_rov_info(sensor_t *sensor_data)
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

cJSON *get_rov_debug_info(debug_info_t *info)
{
    cJSON* cjson_pid_feedbacks = cJSON_CreateObject();
    cJSON* cjson_pid_control_loops = cJSON_CreateObject();

    cJSON_AddNumberToObject(cjson_pid_control_loops, "depth_lock", info->depth_diffen);
    cJSON_AddNumberToObject(cjson_pid_control_loops, "direction_lock", info->yaw_diffen);
    cJSON_AddItemToObject(cjson_pid_feedbacks, "control_loops", cjson_pid_control_loops);

    return cjson_pid_feedbacks;
}

cJSON *move_analysis(cJSON* params, struct rov_info* info, move_mode_t mode)
{
    info->devCtl.lose_clt_flag = 0;

    info->rocket.x = cjson_value_analysis_double(params, "x");
    info->rocket.y = cjson_value_analysis_double(params, "y");
    info->rocket.z = cjson_value_analysis_double(params, "z");
    switch (mode)
    {
        case rocket_ctl:
            info->rocket.yaw = cjson_value_analysis_double(params, "rot");
            break;
        case abs_ctl:
            info->rocket.yaw = 0;
//            Total_Controller.Yaw_Angle_Control.Expect = -cjson_value_analysis_double(params, "rot");
            break;
        case rel_clt:
            info->rocket.yaw = 0;
//            expect_rotate_auv = -cjson_value_analysis_double(params, "rot");
            break;
    }
    return cJSON_CreateNull();
}
