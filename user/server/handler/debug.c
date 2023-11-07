#include "config/parameters/propeller.h"
#include "device/application/pwm_controller.h"
#include "config/parameters/utils.h"

#include "config/config.h"
#include "data_define.h"

#include "debug.h"

/**
 * @brief 调试模式状态更新
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *set_debug_mode_enabled_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((struct status_flag *)ctx->data)->debug_mode = params->child->valueint;
    return cJSON_CreateNull();
}

/**
 * @brief 推进器PWM频率设置
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据（上位机提供参数）
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *set_propeller_pwm_freq_calibration_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    rov_info_t *info = (rov_info_t *)ctx->data;
    pthread_mutex_lock(&info->system.device.power_output_mtx);
    pwm_controller_set_freq((uint16_t)params->child->valueint);
    pthread_mutex_unlock(&info->system.device.power_output_mtx);
    return cJSON_CreateNull();
}

/**
 * @brief 推进器参数更新
 * @param ctx 下位机数据（rpc）
 * @param params cJSON数据
 * @param id id
 * @return item（type = CJSON_NULL）
 */
cJSON *set_propeller_values_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    rov_info_t *info = (rov_info_t *)ctx->data;

    info->propeller.back_left.power_debug = cjson_value_analysis_int(params, "back_left");
    info->propeller.back_right.power_debug = cjson_value_analysis_int(params, "back_right");
    info->propeller.center_left.power_debug = cjson_value_analysis_int(params, "center_left");
    info->propeller.center_right.power_debug = cjson_value_analysis_int(params, "center_right");
    info->propeller.front_left.power_debug  = cjson_value_analysis_int(params, "front_left");
    info->propeller.front_right.power_debug  = cjson_value_analysis_int(params, "front_right");

    pthread_cond_signal(&info->system.server.recv_cmd_cond);

    return cJSON_CreateNull();
}

/**
 * @brief config文件更新
 * @param params 机器人配置信息
 * @return item（type = CJSON_NULL）
 */
cJSON *save_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (rov_config_write_json_to_file(params) == 0)
        rov_config_read_from_file(ctx->data);
    return cJSON_CreateNull();
}

/**
 * @brief 读取config配置文件
 * @return cjson
 */
cJSON *load_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return rov_config_read_from_file_return_cjson();
}
