#ifndef UVM_CAL_H
#define UVM_CAL_H

#include "tcp_server.h"
#include "mjsonrpc.h"

#include <stdint.h>
#include <pthread.h>

typedef struct uvm_cal
{
    jrpc_server_t *server;
    mjrpc_handle_t rpc;
    pthread_t server_tid;
} uvm_cal_t;

int uvm_cal_init (uvm_cal_t *handler, uint16_t http_port);
int uvm_cal_start_thread (uvm_cal_t *handler);
int uvm_cal_stop_thread (uvm_cal_t *handler);

#endif
