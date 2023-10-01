#define LOG_TAG "control.main"

#include <elog.h>
#include <unistd.h>
#include <pthread.h>
#include "other.h"

#include "ctrlPart/manual_ctl.h"
#include "ctrlPart/rotate_ctl.h"
#include "ctrlPart/depth_ctl.h"
#include "pid.h"

#include "../device/application/pwm_controller.h"

#include "control.h"

#define CALL_FOR_ALL_PROPELLER(function) \
    function(front_left) \
    function(front_right) \
    function(center_left) \
    function(center_right) \
    function(back_left) \
    function(back_right)

void write_to_propeller(propeller_t *param)
{
    #define PWM_COTROLLER_WRITE(propeller) \
        pwm_controller_write(param->propeller.channel, 0.0f, 7.5 + constrain(5.0 * param->propeller.power_cur, -5.0, 5.0));\
        param->propeller.power_last = param->propeller.power_cur;\
        param->propeller.power_cur = 0;
        
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE)
    #undef PWM_COTROLLER_WRITE
}

void *control_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;
    for (;;)
    {
        rov_manual_control(info);
        if (info->devCtl.debug_mode_stat)
            write_to_propeller(&info->propeller);
        else
        {
            info->propeller.front_left.power_cur = (double)info->debugInfo.propeller_direct_front_left / 1000.0;
            info->propeller.front_right.power_cur = (double)info->debugInfo.propeller_direct_front_right / 1000.0;
            info->propeller.center_left.power_cur = (double)info->debugInfo.propeller_direct_center_left / 1000.0;
            info->propeller.center_right.power_cur = (double)info->debugInfo.propeller_direct_center_right / 1000.0;
            info->propeller.back_left.power_cur = (double)info->debugInfo.propeller_direct_back_left / 1000.0;
            info->propeller.back_right.power_cur = (double)info->debugInfo.propeller_direct_back_right / 1000.0;
            write_to_propeller(&info->propeller);
        }
        rov_delay(10);
    }
    return NULL;
}

int rov_control_run(struct rov_info* info)
{
    log_i("starting thread");
    if (pthread_create(&info->threadTid.control, NULL, control_thread, info) != 0)
    {
        log_e("thread start failed");
        return -1;
    }
    pthread_detach(info->threadTid.control);
    return 0;
}

int rov_control_stop(struct rov_info* info)
{
    if (pthread_cancel(info->threadTid.control) != 0)
    {
        log_e("cancel thread failed");
        return -1;
    }
    return 0;
}
