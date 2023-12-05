#ifndef UVM_CAL_TCP_SERVER_H
#define UVM_CAL_TCP_SERVER_H

#include <netdb.h>
#include <sys/epoll.h>

#define SERVER_MAX_CONN               16
#define SERVER_MAX_EVENTS             32
#define SERVER_INITIAL_BUFFER_SIZE    128

#define SERVER_LVL_INFO  1
#define SERVER_LVL_DEBUG 2

typedef struct jrpc_server
{
    int debug_level;
    char *buf_head;
    int buf_size;
    int epfd;
    int socklen;
    int conn_sock;
    int listen_sock;
    struct sockaddr_in srv_addr;
    struct sockaddr_in cli_addr;
    struct epoll_event events[SERVER_MAX_EVENTS];
    char *(*handle_recv)(const char *data, int len);
} jrpc_server_t;

#define tcp_server_set_debug_level(handle, level) (handle)->debug_level = level
#define tcp_server_set_recv_handle(handle, func) (handle)->handle_recv = func

jrpc_server_t *tcp_server_init(uint16_t port);
void tcp_server_run_loop(jrpc_server_t *handle);
int tcp_server_deinit(jrpc_server_t *handle);

#endif
