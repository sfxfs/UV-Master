#ifndef UVM_CAL_RPC_FUN_H
#define UVM_CAL_RPC_FUN_H

#include "rpc-cjson.h"
#include "uvm-cfg.h"

int add_all_handler(rpc_handle_t *handle, config_data *cfg);

cJSON *empty_handler(jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *manual_ctrl(jrpc_context *ctx, cJSON *params, cJSON *id);

#endif
