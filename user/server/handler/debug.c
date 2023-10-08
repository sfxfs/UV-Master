#include "config/parameters/pid_ctl.h"
#include "config/parameters/propeller.h"

#include "config/config.h"
#include "data_define.h"

#include "debug.h"

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

cJSON *set_debug_mode_enabled_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    ((dev_ctl_t *)ctx->data)->debug_mode_stat = params->child->valueint;
    return cJSON_CreateNull();
}

cJSON *set_propeller_pwm_freq_calibration_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    ((rov_info_t *)ctx->data)->propeller.pwm_freq_calibration = params->child->valuedouble;
    pthread_mutex_unlock(&((rov_info_t *)ctx->data)->thread.mutex.pwm_controller_reset_freq);
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

cJSON *set_propeller_parameters_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    propeller_params_read_from_root(&((propeller_t *)ctx->data)->front_right, cJSON_GetObjectItem(params, "front_right"));
    propeller_params_read_from_root(&((propeller_t *)ctx->data)->front_left, cJSON_GetObjectItem(params, "front_left"));
    propeller_params_read_from_root(&((propeller_t *)ctx->data)->center_right, cJSON_GetObjectItem(params, "center_right"));
    propeller_params_read_from_root(&((propeller_t *)ctx->data)->center_left, cJSON_GetObjectItem(params, "center_left"));
    propeller_params_read_from_root(&((propeller_t *)ctx->data)->back_right, cJSON_GetObjectItem(params, "back_right"));
    propeller_params_read_from_root(&((propeller_t *)ctx->data)->back_left, cJSON_GetObjectItem(params, "back_left"));
    return cJSON_CreateNull();
}

cJSON *set_control_loop_parameters_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    pid_ctl_params_read_from_root(&((pid_scale_t *)ctx->data)->yaw, cJSON_GetObjectItem(params, "yaw_lock"));
    pid_ctl_params_read_from_root(&((pid_scale_t *)ctx->data)->depth, cJSON_GetObjectItem(params, "depth_lock"));
    return cJSON_CreateNull();
}

cJSON *save_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    rov_config_write_to_file(ctx->data);
    return cJSON_CreateNull();
}

cJSON *load_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    // for compatibility
    rov_info_t *info = (rov_info_t *)ctx->data;
    cJSON* root = cJSON_CreateObject();
    cJSON* propeller_parameters = cJSON_CreateObject();
    cJSON* control_loop_parameters = cJSON_CreateObject();

    cJSON_AddNumberToObject(root, "propeller_pwm_freq_calibration", info->propeller.pwm_freq_calibration);

    cJSON_AddItemToObject(propeller_parameters, "front_right", propeller_params_add_to_root(&info->propeller.front_right));
    cJSON_AddItemToObject(propeller_parameters, "front_left", propeller_params_add_to_root(&info->propeller.front_left));
    cJSON_AddItemToObject(propeller_parameters, "center_right", propeller_params_add_to_root(&info->propeller.center_right));
    cJSON_AddItemToObject(propeller_parameters, "center_left", propeller_params_add_to_root(&info->propeller.center_left));
    cJSON_AddItemToObject(propeller_parameters, "back_right", propeller_params_add_to_root(&info->propeller.back_right));
    cJSON_AddItemToObject(propeller_parameters, "back_left", propeller_params_add_to_root(&info->propeller.back_left));

    cJSON_AddItemToObject(root, "propeller_parameters", propeller_parameters);

    cJSON_AddItemToObject(control_loop_parameters, "yaw_lock", pid_ctl_params_add_to_root(&info->pidScale.yaw));
    cJSON_AddItemToObject(control_loop_parameters, "depth_lock", pid_ctl_params_add_to_root(&info->pidScale.depth));

    cJSON_AddItemToObject(root, "control_loop_parameters", control_loop_parameters);

    return root;
}
