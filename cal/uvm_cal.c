#include "uvm_cal.h"

#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static char *on_recv(const char *data, int len, void *arg)
{
    /* get body */
	char *body = uvm_strstr(data, len, "\r\n\r\n");
    if (body != NULL) {
        body += 4;    // "\r\n\r\n"
        len = len - (data - body);
    } else
        len = 0;

    /* rpc process */
    char *jresp = rpc_process(arg, body, len);
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

#undef HTTP_HEADER_BUF_SIZE

static void *server_thread(void *arg)
{
    for (;;)
        tcp_server_run_loop(arg);
    return NULL;
}

int uvm_cal_init (uvm_cal_t *handler, uint16_t http_port)
{
    if (handler)
        memset(handler, 0, sizeof(uvm_cal_t));
    else
        return -1;
    handler->server = tcp_server_init(http_port, &handler->rpc);
    if (handler->server == NULL)
    {
        log_error("Server init failed.");
        return -2;
    }
    tcp_server_set_recv_handle(handler->server, on_recv);
    log_info("Server init success.");
    return 0;
}

int uvm_cal_start_thread (uvm_cal_t *handler)
{
    if (pthread_create(&handler->server_tid, NULL, server_thread, handler->server) != 0)
    {
        log_error("Thread start failed.");
        return -1;
    }
    pthread_detach(handler->server_tid);
    return 0;
}

int uvm_cal_stop_thread (uvm_cal_t *handler)
{
    if (pthread_cancel(handler->server_tid) != 0)
        log_warn("Thread stop failed.");
    return tcp_server_deinit(handler->server);
}
