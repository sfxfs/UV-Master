#define LOG_TAG "control.main"

#include <elog.h>
#include <unistd.h>
#include <pthread.h>

#include "ctrlPart/manual_ctl.h"
#include "ctrlPart/rotate_ctl.h"
#include "ctrlPart/depth_ctl.h"

#include "control.h"

void *control_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;
    for (;;)
    {
        pthread_mutex_lock(&info->thread.mutex.cal_rocket_output);
        if (info->devCtl.debug_mode_stat == true) {
            info->propeller.front_left.power_cur = (float)info->debugInfo.propeller_direct_front_left / 500.0f;
            info->propeller.front_right.power_cur = (float)info->debugInfo.propeller_direct_front_right / 500.0f;
            info->propeller.center_left.power_cur = (float)info->debugInfo.propeller_direct_center_left / 500.0f;
            info->propeller.center_right.power_cur = (float)info->debugInfo.propeller_direct_center_right / 500.0f;
            info->propeller.back_left.power_cur = (float)info->debugInfo.propeller_direct_back_left / 500.0f;
            info->propeller.back_right.power_cur = (float)info->debugInfo.propeller_direct_back_right / 500.0f;
        }else {
            rov_manual_control(info);
        }
        pthread_mutex_unlock(&info->thread.mutex.write_propeller);
    }
    return NULL;
}

int rov_control_run(struct rov_info* info)
{
    if (pthread_mutex_init(&info->thread.mutex.cal_rocket_output, NULL) != 0)
    {
        log_e("cannot init cal_rocket_output mutex");
        return -1;
    }
    log_i("starting thread");
    if (pthread_create(&info->thread.tid.control, NULL, control_thread, info) != 0)
    {
        log_e("thread start failed");
        return -1;
    }
    pthread_detach(info->thread.tid.control);
    return 0;
}

int rov_control_stop(struct rov_info* info)
{
    if (pthread_cancel(info->thread.tid.control) != 0)
    {
        log_e("cancel thread failed");
    }
    if (pthread_mutex_destroy(&info->thread.mutex.cal_rocket_output) != 0)
    {
        log_e("destroy mutex cal_rocket_output failed");
        return -1;
    }
    return 0;
}
