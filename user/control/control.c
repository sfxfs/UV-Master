#define LOG_TAG "control.main"

#include <elog.h>
#include <unistd.h>
#include <pthread.h>

#include "ctrlPart/horizon.h"
#include "ctrlPart/rotate.h"
#include "ctrlPart/depth.h"
#include "pid.h"

#include "../device/application/pwm_controller.h"

#include "control.h"

#define CALL_FOR_ALL_PROPELLER(function) \
    function(PCA9685_CHANNEL_0,front_left) \
    function(PCA9685_CHANNEL_1,front_right) \
    function(PCA9685_CHANNEL_2,center_left) \
    function(PCA9685_CHANNEL_3,center_right) \
    function(PCA9685_CHANNEL_4,back_left) \
    function(PCA9685_CHANNEL_5,back_right)

void write_to_propeller(propeller_t *param)
{
    #define PWM_COTROLLER_WRITE(channel,propeller) \
        pwm_controller_write(channel, 0.0f, 7.5f + constrain(5.0f * param->propeller.power_cur, -5.0f, 5.0f));
        
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE)
    #undef PWM_COTROLLER_WRITE
}

void *control_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;
    for (;;)
    {
        rov_horizon_control(info);
        rov_rotate_control(info);
        rov_depth_control(info);
        write_to_propeller(&info->propeller);
        usleep(10 * 1000);
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
        return -1;
    }
    return 0;
}
