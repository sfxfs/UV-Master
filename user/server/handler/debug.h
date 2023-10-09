#ifndef SERVER_HANDLER_DEBUG_H
#define SERVER_HANDLER_DEBUG_H

#include <jsonrpc-c.h>

cJSON *set_debug_mode_enabled_handler               (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *set_propeller_pwm_freq_calibration_handler   (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *set_propeller_values_handler                 (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *set_propeller_parameters_handler             (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *set_control_loop_parameters_handler          (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *save_handler                                 (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *load_handler                                 (jrpc_context *ctx, cJSON *params, cJSON *id);

#endif