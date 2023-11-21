#ifndef DATA_DEFINE_SYSTEM_H
#define DATA_DEFINE_SYSTEM_H

#include <pthread.h>

typedef struct sys_device
{
    pthread_t main_tid;
    pthread_cond_t power_output_cond;
    pthread_mutex_t power_output_mtx;
} sys_device_t;

struct server_config
{
    char *port;
    time_t clt_timeout; // ms
};

typedef struct sys_server
{
    pthread_t loss_status_check_tid;
    pthread_mutex_t loss_status_mtx;
    struct server_config config;
} sys_server_t;

typedef struct sys_control
{
    pthread_t main_tid;
    pthread_mutex_t recv_cmd_mtx;
    pthread_cond_t recv_cmd_cond;
} sys_control_t;

typedef struct system
{
    struct sys_device device;
    struct sys_server server;
    struct sys_control control;
} system_t;

#endif
