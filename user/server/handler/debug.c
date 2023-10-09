#include "config/parameters/pid_ctl.h"
#include "config/parameters/propeller.h"
#include "device/application/pwm_controller.h"
#include "config/parameters/utils.h"

#include "config/config.h"
#include "data_define.h"

#include "debug.h"

cJSON *set_debug_mode_enabled_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    ((dev_ctl_t *)ctx->data)->debug_mode_stat = params->child->valueint;
    return cJSON_CreateNull();
}

cJSON *set_propeller_pwm_freq_calibration_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    if (params == NULL)
        return cJSON_CreateNull();
    pwm_controller_set_freq((uint16_t)params->child->valueint);
    return cJSON_CreateNull();
}

cJSON *set_propeller_values_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    rov_info_t *info = (rov_info_t *)ctx->data;

    info->debugInfo.propeller_direct_back_left = cjson_value_analysis_int(params, "back_left");
    info->debugInfo.propeller_direct_back_right = cjson_value_analysis_int(params, "back_right");
    info->debugInfo.propeller_direct_center_left = cjson_value_analysis_int(params, "center_left");
    info->debugInfo.propeller_direct_center_right = cjson_value_analysis_int(params, "center_right");
    info->debugInfo.propeller_direct_front_left  = cjson_value_analysis_int(params, "front_left");
    info->debugInfo.propeller_direct_front_right  = cjson_value_analysis_int(params, "front_right");

    pthread_mutex_unlock(&info->thread.mutex.cal_rocket_output);
    return cJSON_CreateNull();
}

cJSON *save_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    rov_config_write_json_to_file(params);
    return cJSON_CreateNull();
}

cJSON *load_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return rov_config_read_from_file_return_cjson();
}
