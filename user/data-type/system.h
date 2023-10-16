#ifndef DATA_DEFINE_SYSTEM_H
#define DATA_DEFINE_SYSTEM_H

#include <pthread.h>

struct thread_tid
{
    pthread_t rpc_server;
    pthread_t device;
    pthread_t control;
    pthread_t propeller;
    pthread_t loss_status_check;
};

struct thread_mutex
{
    pthread_mutex_t write_propeller;
    pthread_mutex_t cal_rocket_output;
};

typedef struct rov_thread
{
    struct thread_tid tid;
    struct thread_mutex mutex;
} rov_thread_t;

typedef struct server_config
{
    int port;
    time_t clt_timeout;
} server_config_t;


#endif
