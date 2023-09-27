//
// Created by fxf on 23-8-29.
//

#define LOG_TAG "device.main"

#include <elog.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/epoll.h>

#include "application/pwm_controller.h"
#include "application/depth_sensor.h"
#include "application/motion_sensor.h"

#include "device.h"

void *device_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;

    for (;;)
    {

    }

    return NULL;
}

int rov_device_run(struct rov_info* info)
{
    if (pwm_controller_init(0x40, 50) < 0)
    {
        log_e("pwm controller init failed");
        return -1;
    }
    return 0;
}

int rov_device_stop(struct rov_info* info)
{
    if (pwm_controller_deinit() < -1)
    {
        log_e("pwm controller deinit failed");
        return -1;
    }
    return 0;
}
