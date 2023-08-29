//
// Created by fxf on 23-8-29.
//

#ifndef ROV_MASTER_DEVICE_H
#define ROV_MASTER_DEVICE_H

#include "../data_define.h"

#define DEVICE_EPOLL_MAX_EVENT 10
#define DEVICE_EPOLL_WAIT_MS 100

int rov_device_run(struct rov_info* info);
int rov_device_stop(struct rov_info* info);

#endif //ROV_MASTER_DEVICE_H
