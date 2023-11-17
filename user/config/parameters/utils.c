#include "utils.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief 获取 json 内对应值
 * @param params cjson结构体
 * @param str 值对应字符串
 * @return 获得的浮点数，若没有获取到则为 0
 */
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

/**
 * @brief 获取 json 内对应值
 * @param params cjson结构体
 * @param str 值对应字符串
 * @return 获得的整形数，若没有获取到则为 0
 */
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

/**
 * @brief 获取 json 内对应值
 * @param params cjson结构体
 * @param str 值对应字符串
 * @return 返回获取到的字符串，若没有获取到则为 NULL，用完需要 free
 */
char *cjson_value_analysis_string(cJSON *params, const char *str)
{
    char *temp = cJSON_GetObjectItem(params, str)->valuestring;
    if (temp == NULL)
        return NULL;
    char *ret_str = calloc(strlen(temp) + 1, sizeof(char));
    if (ret_str == NULL)
        return NULL;
    strcpy(ret_str, temp);
    return ret_str;
}
