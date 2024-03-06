#include "rpc_fun.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "control.h"
#include "cJSON.h"

/**
 * @brief 获取 json 内对应值
 * @param params cjson结构体
 * @param str 值对应字符串
 * @return 获得的浮点数，若没有获取到则为 0
 */
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

/**
 * @brief 获取 json 内对应值
 * @param params cjson结构体
 * @param str 值对应字符串
 * @return 获得的整形数，若没有获取到则为 0
 */
static __attribute__((__unused__)) int cjson_value_analysis_int(cJSON *params, const char *str)
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
static __attribute__((__unused__)) char *cjson_value_analysis_string(cJSON *params, const char *str)
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

//---------------------------------------------------------------------------------

static cJSON *get_rov_info()
{
    cJSON *cjson_info = NULL;
    cjson_info = cJSON_CreateObject();
    char *temp_str = malloc(sizeof(char) * 20);
    sprintf(temp_str, "%.02f ℃", 0.0f);
    cJSON_AddStringToObject(cjson_info, "温度", temp_str);
    sprintf(temp_str, "%.02f °", 0.0f);
    cJSON_AddStringToObject(cjson_info, "航向角", temp_str);
    sprintf(temp_str, "%.02f cm", 0.0f);
    cJSON_AddStringToObject(cjson_info, "深度", temp_str);
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
    return get_rov_info();
}

cJSON *empty_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return cJSON_CreateNull();
}

cJSON *manual_ctrl(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (rpc_manual_ctrl((config_data *)ctx->data, cjson_value_analysis_double(params, "x"), cjson_value_analysis_double(params, "y"), cjson_value_analysis_double(params, "z"), cjson_value_analysis_double(params, "rot")) != 0)
    {
        ctx->error_code = JRPC_INTERNAL_ERROR;
        ctx->error_message = strdup("Write to pwm controller failed.");
    }
    return cJSON_CreateNull();
}

int rpc_add_all_handler(rpc_handle_t *handle, config_data *cfg)
{
    int ret = 0;
    ret += rpc_add_method(handle, info_handler, "get_info", NULL);
    ret += rpc_add_method(handle, empty_handler, "catch", NULL);
    ret += rpc_add_method(handle, empty_handler, "light", NULL);
    ret += rpc_add_method(handle, empty_handler, "set_direction_locked", NULL);
    ret += rpc_add_method(handle, empty_handler, "set_depth_locked", NULL);

    ret += rpc_add_method(handle, manual_ctrl, "move", cfg);
    return ret;
}
