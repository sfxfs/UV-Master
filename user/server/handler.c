#include "handler_function.h"
#include "handler.h"

cJSON *info_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return get_rov_info(ctx->data);
}

cJSON *debug_info_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *update_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}


cJSON *move_asyn_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, 0);
}

cJSON *move_syn_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, 0);
}

cJSON *catcher_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *depth_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *move_absolute_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, 1);
}

cJSON *move_relative_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{
    return move_analysis(params, ctx->data, 2);
}

cJSON *direction_lock_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *depth_lock_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}


cJSON *set_debug_mode_enabled_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *set_propeller_pwm_freq_calibration_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *set_propeller_values_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *set_propeller_parameters_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *set_control_loop_parameters_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *save_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}

cJSON *load_handler(jrpc_context *ctx, cJSON *params, cJSON *id)
{

}
