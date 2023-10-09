#include "data_define.h"

#include "control.h"

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

static cJSON *move_analysis(cJSON* params, struct rov_info* info, move_mode_t mode)
{
    if (params == NULL)
        return cJSON_CreateNull();
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
            break;
        case rel_clt:
            info->rocket.yaw = 0;
            break;
    }

    pthread_mutex_unlock(&info->thread.mutex.cal_rocket_output);
    info->devCtl.lose_clt_flag = 0;

    return cJSON_CreateNull();
}

cJSON *move_asyn_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, rocket_ctl);
}

cJSON *move_syn_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, rocket_ctl);
}

cJSON *catcher_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((dev_ctl_t *)ctx->data)->catcher_clt = params->child->valuedouble > 0 ? pwm_pMove : (params->child->valuedouble < 0 ? pwm_nMove : pwm_noAct);
    return cJSON_CreateNull();
}

cJSON *light_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((dev_ctl_t *)ctx->data)->light_clt = params->child->valuedouble > 0 ? pwm_pMove : (params->child->valuedouble < 0 ? pwm_nMove : pwm_noAct);
    return cJSON_CreateNull();
}

cJSON *depth_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((debug_info_t *)ctx->data)->auv_expect_depth = (float)params->child->valuedouble;
    return cJSON_CreateNull();
}

cJSON *move_absolute_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, abs_ctl);
}

cJSON *move_relative_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, rel_clt);
}

cJSON *direction_lock_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((dev_ctl_t *)ctx->data)->dir_lock = params->child->valueint;
    return cJSON_CreateNull();
}

cJSON *depth_lock_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((dev_ctl_t *)ctx->data)->depth_lock = params->child->valueint;
    return cJSON_CreateNull();
}