#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include "../../protocols/jsonrpc-c.h"

cJSON *info_handler                                 (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *debug_info_handler                           (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *update_handler                               (jrpc_context *ctx, cJSON *params, cJSON *id);

cJSON *move_asyn_handler                            (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *move_syn_handler                             (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *catcher_handler                              (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *depth_handler                                (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *move_absolute_handler                        (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *move_relative_handler                        (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *direction_lock_handler                       (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *depth_lock_handler                           (jrpc_context *ctx, cJSON *params, cJSON *id);

cJSON *set_debug_mode_enabled_handler               (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *set_propeller_pwm_freq_calibration_handler   (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *set_propeller_values_handler                 (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *set_propeller_parameters_handler             (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *set_control_loop_parameters_handler          (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *save_handler                                 (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *load_handler                                 (jrpc_context *ctx, cJSON *params, cJSON *id);

#endif
