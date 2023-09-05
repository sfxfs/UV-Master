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
    ((dev_ctl_t *)ctx->data)->catcher_clt = params->child->valuedouble > 0 ? 1 : (params->child->valuedouble < 0 ? 2 : 0);
    return cJSON_CreateNull();
}

cJSON *light_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    ((dev_ctl_t *)ctx->data)->light_clt = params->child->valuedouble > 0 ? 1 : (params->child->valuedouble < 0 ? 2 : 0);
    return cJSON_CreateNull();
}

cJSON *depth_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
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
    return cJSON_CreateNull();
}

cJSON *set_propeller_values_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return cJSON_CreateNull();
}

cJSON *set_propeller_parameters_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return cJSON_CreateNull();
}

cJSON *set_control_loop_parameters_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return cJSON_CreateNull();
}

cJSON *save_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return cJSON_CreateNull();
}

cJSON *load_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return cJSON_CreateNull();
}
