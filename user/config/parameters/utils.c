#include "utils.h"

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
