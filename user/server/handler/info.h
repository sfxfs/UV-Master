#ifndef SERVER_HANDLER_INFO_H
#define SERVER_HANDLER_INFO_H

#include <rpc_cjson.h>

cJSON *info_handler         (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *debug_info_handler   (jrpc_context *ctx, cJSON *params, cJSON *id);
cJSON *update_handler       (jrpc_context *ctx, cJSON *params, cJSON *id);

#endif
