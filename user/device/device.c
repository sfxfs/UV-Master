//
// Created by fxf on 23-8-29.
//

#define LOG_TAG "device.main"

#include <elog.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <unistd.h>
#include "application/pwm_controller.h"
#include "application/depth_sensor.h"
#include "application/motion_sensor.h"

#include "device.h"

static int dev_epoll_fd;

static int device_epoll_init(struct rov_info* info)
{
    dev_epoll_fd = epoll_create1(0);
    if (dev_epoll_fd < 0)
    {
        log_e("epoll create failed");
        return -1;
    }
    struct epoll_event ev;

    ev.data.fd = info->devFd.depth_sensor_fd;
    ev.events = EPOLLIN;
    if (epoll_ctl(dev_epoll_fd, EPOLL_CTL_ADD, info->devFd.depth_sensor_fd, &ev) < 0)
    {
        log_e("cannot add depth sensor to epoll");
    }

    ev.data.fd = info->devFd.motion_sensor_fd;
    ev.events = EPOLLIN;
    if (epoll_ctl(dev_epoll_fd, EPOLL_CTL_ADD, info->devFd.motion_sensor_fd, &ev) < 0)
    {
        log_e("cannot add motion sensor to epoll");
    }

    return 0;
}

void *device_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;
    int nfds, n;
    struct epoll_event events[DEVICE_EPOLL_MAX_EVENT];
    for (;;)
    {
        nfds = epoll_wait(dev_epoll_fd, events, DEVICE_EPOLL_MAX_EVENT, -1);
        if (nfds == -1)
        {
            log_e("epoll wait error");
            break;
        }

        for (n = 0; n < nfds; ++n)
        {

        }
    }
    return NULL;
}

int rov_device_run(struct rov_info* info)
{
    info->devFd.pwm_controller_fd = pwm_controller_init(PCA9685_ADDRESS_A111111, 50);
    info->devFd.depth_sensor_fd = -1;
    info->devFd.motion_sensor_fd = -1;

    if (info->devFd.pwm_controller_fd < 0)
    {
        log_e("pwm controller init failed");
        return -1;
    }

    if (info->devFd.depth_sensor_fd < 0)
    {
        log_e("depth sensor init failed");
    }

    if (info->devFd.motion_sensor_fd < 0)
    {
        log_e("motion sensor_fd init failed");
    }

    if (device_epoll_init(info) != 0)
    {
        log_e("epoll init failed");
        return -1;
    }

    log_i("starting thread");
    if (pthread_create(&info->threadTid.device, NULL, device_thread, info) != 0)
    {
        log_e("thread start failed");
        return -1;
    }
    pthread_detach(info->threadTid.device);
    return 0;
}

int rov_device_stop(struct rov_info* info)
{
    int res = 0;
    if (pthread_cancel(info->threadTid.device) != 0)
    {
        log_e("cannot cancel thread (may init failed)");
        res = -1;
    }
    close(dev_epoll_fd);
    pwm_controller_deinit();
    return res;
}
