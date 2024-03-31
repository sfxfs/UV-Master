#include "tcp_server.h"

#include "log.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

static int epoll_ctl_add(int epfd, int fd, uint32_t events)
{
	struct epoll_event ev;
	ev.events = events;
	ev.data.fd = fd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
		return -1;
    return 0;
}

static int setnonblocking(int sockfd)
{
	if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK) ==
	    -1) {
		return -1;
	}
	return 0;
}

jrpc_server_t *tcp_server_init(uint16_t port, void *arg)
{
    jrpc_server_t *handle = calloc(1, sizeof(jrpc_server_t));
    if (handle == NULL)
        return NULL;

    handle->listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (handle->listen_sock < 0)
    {
        log_debug("Get socket fd failed.");
        free(handle);
        return NULL;
    }

    int reuse = 1;
    if (setsockopt(handle->listen_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        free(handle);
        return NULL;
    }

    bzero((char *)&handle->srv_addr, sizeof(struct sockaddr_in));
	handle->srv_addr.sin_family = AF_INET;
	handle->srv_addr.sin_addr.s_addr = INADDR_ANY;
	handle->srv_addr.sin_port = htons(port);
    handle->arg2recv = arg;

    int ret = bind(handle->listen_sock, (struct sockaddr *)&handle->srv_addr, sizeof(struct sockaddr_in));
    if (ret != 0)
    {
        log_debug("Bind port to %d failed.", port);
        free(handle);
        return NULL;
    }

    setnonblocking(handle->listen_sock);
	ret = listen(handle->listen_sock, SERVER_MAX_CONN);
    if (ret != 0)
    {
        free(handle);
        return NULL;
    }

    handle->epfd = epoll_create(1);
	ret = epoll_ctl_add(handle->epfd, handle->listen_sock, EPOLLIN | EPOLLOUT | EPOLLET);
    if (ret != 0)
    {
        free(handle);
        return NULL;
    }

	handle->socklen = sizeof(handle->cli_addr);
    handle->buf_head = calloc(SERVER_INITIAL_BUFFER_SIZE, sizeof(char));
    handle->buf_size = SERVER_INITIAL_BUFFER_SIZE;

    return handle;
}

void tcp_server_run_loop(jrpc_server_t *handle)
{
    int nfds = epoll_wait(handle->epfd, handle->events, SERVER_MAX_EVENTS, -1);
    for (int i = 0; i < nfds; i++)
    {
        if (handle->events[i].data.fd == handle->listen_sock)
        {
            /* handle new connection */
            handle->conn_sock =
                accept(handle->listen_sock,
                       (struct sockaddr *)&handle->cli_addr,
                       (unsigned int *)&handle->socklen);
                inet_ntop(AF_INET, (char *)&(handle->cli_addr.sin_addr),
                          handle->buf_head, sizeof(handle->cli_addr));
                log_debug("Connected with %s:%d.", handle->buf_head,
                       ntohs(handle->cli_addr.sin_port));

            setnonblocking(handle->conn_sock);
            epoll_ctl_add(handle->epfd, handle->conn_sock,
                          EPOLLIN | EPOLLET | EPOLLRDHUP |
                              EPOLLHUP);
        }
        else if (handle->events[i].events & EPOLLIN)
        {
            int buf_used = 0;
            int buf_free = handle->buf_size;
            int bytes_read;
            /* handle EPOLLIN event */
            bzero(handle->buf_head, handle->buf_size);
            for (;;)
            {
                bytes_read = read(handle->events[i].data.fd, handle->buf_head + buf_used,
                         buf_free);
            	buf_used += bytes_read;
                if (bytes_read == buf_free)
                {
                    handle->buf_head = realloc(handle->buf_head, handle->buf_size *= 2);
                    bzero(handle->buf_head + buf_used, handle->buf_size - buf_used);
                    buf_free = handle->buf_size - buf_used;
                	log_debug("Recv buf resize to: %d Byte", handle->buf_size);
                    continue;
                }
                if (bytes_read <= 0)
                    break;

                log_trace("Data recv: \n%.*s", buf_used, handle->buf_head);

                char *ret_str = handle->handle_recv(handle->buf_head, buf_used, handle->arg2recv);
                log_trace("Data send: \n%s", ret_str);
                write(handle->events[i].data.fd, ret_str, strlen(ret_str));
                free(ret_str);

                break;
            }
        }
        else
        {
            log_error("Unexpected error.");
        }
        /* check if the connection is closing */
        if (handle->events[i].events & (EPOLLRDHUP | EPOLLHUP))
        {
            log_debug("Connection closed.");
            epoll_ctl(handle->epfd, EPOLL_CTL_DEL,
                      handle->events[i].data.fd, NULL);
            close(handle->events[i].data.fd);
            continue;
        }
    }
}

int tcp_server_deinit(jrpc_server_t *handle)
{
    free(handle->buf_head);
    int ret = 0;
    ret += close(handle->epfd);
    ret += close(handle->listen_sock);
    ret += close(handle->conn_sock);
    free(handle);
    return ret;
}
