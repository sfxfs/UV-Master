#include "config/parameters/utils.h"
#include "data_define.h"

#include "control.h"

/**
 * @brief 运动模式选择线程
 * @param params cJSON参数（储存有xyz轴的移动信息）
 * @param info rov_info结构体参数
 * @param mode rocket_ctl ； abs_ctl ； rel_clt ;
 * @return item（type = CJSON_NULL）
 */
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

/**
 * @brief 手柄数据处理
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机提供手柄参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *move_asyn_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, rocket_ctl);
}

cJSON *move_syn_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, rocket_ctl);
}

/**
 * @brief 机械臂数据更新
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机提供手柄参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *catcher_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((dev_ctl_t *)ctx->data)->catcher_clt = params->child->valuedouble > 0 ? pwm_pMove : (params->child->valuedouble < 0 ? pwm_nMove : pwm_noAct);
    return cJSON_CreateNull();
}

/**
 * @brief 灯光数据更新
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机提供手柄参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *light_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((dev_ctl_t *)ctx->data)->light_clt = params->child->valuedouble > 0 ? pwm_pMove : (params->child->valuedouble < 0 ? pwm_nMove : pwm_noAct);
    return cJSON_CreateNull();
}

/**
 * @brief 期望深度更新
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机提供手柄参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *depth_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((debug_info_t *)ctx->data)->auv_expect_depth = (float)params->child->valuedouble;
    return cJSON_CreateNull();
}

/**
 * @brief 绝对角度移动
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机提供手柄参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *move_absolute_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, abs_ctl);
}

/**
 * @brief 相对角度移动
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机提供手柄参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *move_relative_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, rel_clt);
}

/**
 * @brief 方向锁定期望角度更新
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机提供参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *direction_lock_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((dev_ctl_t *)ctx->data)->dir_lock = params->child->valueint;
    return cJSON_CreateNull();
}

/**
 * @brief 深度锁定期望深度更新
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机提供参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *depth_lock_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((dev_ctl_t *)ctx->data)->depth_lock = params->child->valueint;
    return cJSON_CreateNull();
}