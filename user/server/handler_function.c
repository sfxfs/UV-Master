//
// Created by fxf on 23-7-9.
//

#include "handler_function.h"

static int cjson_value_analysis_int(cJSON *params, const char *str)
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

static double cjson_value_analysis_double(cJSON *params,const char *str)
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
    
}

cJSON *move_analysis(cJSON* params, rocket_t* rocket, int mode)
{
    rocket->x = cjson_value_analysis_double(params, "x");
    rocket->y = cjson_value_analysis_double(params, "y");
    rocket->z = cjson_value_analysis_double(params, "z");
    switch (mode)
    {
        case 0:
            rocket->yaw = cjson_value_analysis_double(params, "rot") * 127;
            break;
        case 1:
            rocket->yaw = 0;
//            Total_Controller.Yaw_Angle_Control.Expect = -cjson_value_analysis_double(params, "rot");
            break;
        case 2:
            rocket->yaw = 0;
//            expect_rotate_auv = -cjson_value_analysis_double(params, "rot");
            break;
    }
    return cJSON_CreateNull();
}
