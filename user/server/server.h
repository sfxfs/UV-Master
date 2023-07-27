#ifndef SERVER_MAIN_H
#define SERVER_MAIN_H

#include "../data_define.h"

int jsonrpc_server_run  (struct rov_info* info, int port);
int jsonrpc_server_stop (void);

#endif
