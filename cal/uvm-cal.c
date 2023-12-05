#include <string.h>
#include "rpc-cjson.h"
#include "tcp-server.h"

#include "uvm-cal.h"

#define RPC_PORT 8888

jrpc_server_t *server;
rpc_handle_t rpc;

static char *on_recv(const char *data, int len)
{
	char *locate = strstr(data, "\r\n\r\n");
}

int uvm_cal_start()
{
    server = tcp_server_init(RPC_PORT);
    if (server == NULL)
    {
        return -1;
    }
    tcp_server_set_debug_level(server, SERVER_LVL_DEBUG);
    tcp_server_set_recv_handle(server, on_recv);
}
