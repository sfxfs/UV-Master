#include "../config/parameters/pid_ctl.h"
#include "../config/parameters/propeller.h"
#include "../config/config.h"
#include "handler_function.h"
#include "handler.h"

cJSON *info_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return get_rov_info(ctx->data);
}

cJSON *debug_info_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return get_rov_debug_info(ctx->data);
}

cJSON *update_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
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
    ((dev_ctl_t *)ctx->data)->catcher_clt = params->child->valuedouble > 0 ? pwm_pMove : (params->child->valuedouble < 0 ? pwm_nMove : pwm_noAct);
    return cJSON_CreateNull();
}

cJSON *light_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    ((dev_ctl_t *)ctx->data)->light_clt = params->child->valuedouble > 0 ? pwm_pMove : (params->child->valuedouble < 0 ? pwm_nMove : pwm_noAct);
    return cJSON_CreateNull();
}

cJSON *depth_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
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
    ((dev_ctl_t *)ctx->data)->dir_lock = params->child->valueint;
    return cJSON_CreateNull();
}

cJSON *depth_lock_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    ((dev_ctl_t *)ctx->data)->depth_lock = params->child->valueint;
    return cJSON_CreateNull();
}


cJSON *set_debug_mode_enabled_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    ((dev_ctl_t *)ctx->data)->debug_mode_stat = params->child->valueint;
    return cJSON_CreateNull();
}

cJSON *set_propeller_pwm_freq_calibration_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    ((propeller_t *)ctx->data)->pwm_freq_calibration = params->child->valuedouble;
    return cJSON_CreateNull();
}

cJSON *set_propeller_values_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    ((debug_info_t *)ctx->data)->propeller_direct_back_left    = cjson_value_analysis_int(params, "back_left");
    ((debug_info_t *)ctx->data)->propeller_direct_back_right = cjson_value_analysis_int(params, "back_right");
    ((debug_info_t *)ctx->data)->propeller_direct_center_left = cjson_value_analysis_int(params, "center_left");
    ((debug_info_t *)ctx->data)->propeller_direct_center_right = cjson_value_analysis_int(params, "center_right");
    ((debug_info_t *)ctx->data)->propeller_direct_front_left  = cjson_value_analysis_int(params, "front_left");
    ((debug_info_t *)ctx->data)->propeller_direct_front_right  = cjson_value_analysis_int(params, "front_right");
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
    rov_info_t *info = ctx->data;
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
