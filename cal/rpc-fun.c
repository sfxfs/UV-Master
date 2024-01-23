#include "rpc-fun.h"
#include "rpc/ctrl.h"
#include <string.h>
#include <stdlib.h>

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

/**
 * @brief 获取 json 内对应值
 * @param params cjson结构体
 * @param str 值对应字符串
 * @return 返回获取到的字符串，若没有获取到则为 NULL，用完需要 free
 */
static char *cjson_value_analysis_string(cJSON *params, const char *str)
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

int add_all_handler(rpc_handle_t *handle, config_data *cfg)
{
    int ret = 0;
    ret += rpc_add_method(handle, empty_handler, "get_info", NULL);
    ret += rpc_add_method(handle, empty_handler, "catch", NULL);
    ret += rpc_add_method(handle, empty_handler, "light", NULL);
    ret += rpc_add_method(handle, empty_handler, "set_direction_locked", NULL);
    ret += rpc_add_method(handle, empty_handler, "set_depth_locked", NULL);

    ret += rpc_add_method(handle, manual_ctrl, "move", cfg);
    return ret;
}

cJSON *empty_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return cJSON_CreateNull();
}

cJSON *manual_ctrl(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (rpc_manual_ctrl((config_data *)ctx->data, cjson_value_analysis_double(params, "x"), cjson_value_analysis_double(params, "y"), cjson_value_analysis_double(params, "z"), cjson_value_analysis_double(params, "rot")) == 0)
    {
        ctx->error_code = JRPC_INTERNAL_ERROR;
        ctx->error_message = strdup("Write to pwm controller failed.");
    }
    return cJSON_CreateNull();
}
