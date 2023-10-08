#ifndef SERVER_HANDLER_CONTROL_H
#define SERVER_HANDLER_CONTROL_H

#include <jsonrpc-c.h>

typedef enum move_mode
{
    rocket_ctl = 0,
    abs_ctl,    // 绝对
    rel_clt,    // 相对
} move_mode_t;

typedef enum pwm_mode
{
    pwm_noAct = 0,
    pwm_pMove,
    pwm_nMove,
} pwm_mode_t;

cJSON *move_asyn_handler        (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *move_syn_handler         (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *catcher_handler          (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *light_handler            (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *depth_handler            (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *move_absolute_handler    (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *move_relative_handler    (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *direction_lock_handler   (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *depth_lock_handler       (jrpc_context *ctx, cJSON *params, cJSON *id);

#endif
