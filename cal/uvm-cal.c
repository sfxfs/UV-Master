#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "rpc-cjson.h"
#include "tcp-server.h"

#define RPC_PORT 8888
#define RPC_LOG_LEVEL SERVER_LVL_DEBUG

jrpc_server_t *server;
rpc_handle_t rpc;
pthread_t server_tid;

static char *uvm_strstr(const char *p1, int len, const char *p2)
{
    if (p1 == NULL || p2 == NULL)
        return NULL;
    if (*p2 == '\0' || *p1 == '\0')
        return (char *)p1;

    char *s1 = NULL;
    char *s2 = NULL;
    char *current = (char *)p1;

    for (; *current != '\0'; current++)
    {
        if (len == 0)
            return NULL;

        s1 = current;
        s2 = (char *)p2;

        while ((*s1 != '\0') && (*s2 != '\0') && (*s1 == *s2))
        {
            s1++;
            s2++;
        }

        if (*s2 == '\0')
            return current;
        if (*s1 == '\0')
            return NULL;

        len--;
    }
    return NULL;
}

#define HTTP_HEADER_BUF_SIZE 128

static char *on_recv(const char *data, int len)
{
    /* get body */
	char *body = uvm_strstr(data, len, "\r\n\r\n");
    if (body != NULL) {
        body += 4;    // "\r\n\r\n"
        len = len - (data - body);
    } else
        len = 0;

    /* rpc process */
    char *jresp = rpc_process(&rpc, body, len);
    int jresp_len = strlen(jresp);

    /* build response */
    char *resp = calloc(jresp_len + HTTP_HEADER_BUF_SIZE, sizeof(char));
    sprintf(resp,
            "HTTP/1.1 200 OK\r\nContent-Type: application/json; charset=UTF-8\r\nAccept: application/json\r\nContent-Length: %d\r\n\r\n%s",
            jresp_len, jresp);

    /* end up */
    free(jresp);
    return resp;
}

static void *server_thread(void *arg)
{
    for (;;)
        tcp_server_run_loop(server);
    return NULL;
}

int uvm_cal_start()
{
    server = tcp_server_init(RPC_PORT);
    if (server == NULL)
    {
        return -1;
    }
    tcp_server_set_debug_level(server, RPC_LOG_LEVEL);
    tcp_server_set_recv_handle(server, on_recv);

    if (pthread_create(&server_tid, NULL, server_thread, NULL) != 0)
    {
        return -1;
    }
    pthread_detach(server_tid);
    return 0;
}

int uvm_cal_stop()
{
    pthread_cancel(server_tid);
    return tcp_server_deinit(server);
}
