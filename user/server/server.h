#ifndef SERVER_MAIN_H
#define SERVER_MAIN_H

#include "data_define.h"

int jsonrpc_server_run          (struct rov_info* info, uint8_t debug_level);
int jsonrpc_set_timeout_value   (struct rov_info* info);
int jsonrpc_server_stop         (void);

#endif
