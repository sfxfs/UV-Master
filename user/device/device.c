//
// Created by fxf on 23-8-29.
//

#define LOG_TAG "device.main"

#include <elog.h>
#include <unistd.h>
#include <pthread.h>
#include "other.h"

#include "application/pwm_controller.h"
#include "application/depth_sensor.h"
#include "application/motion_sensor.h"

#include "device.h"

#define CALL_FOR_ALL_PROPELLER(function) \
    function(front_left) \
    function(front_right) \
    function(center_left) \
    function(center_right) \
    function(back_left) \
    function(back_right)

static void write_to_propeller(propeller_t *param)
{
    #define PWM_COTROLLER_WRITE(propeller) \
        pwm_controller_write(param->propeller.channel, 0.0f, 7.5 + constrain(5.0 * param->propeller.power_cur, -5.0, 5.0));\
        param->propeller.power_last = param->propeller.power_cur;\
        param->propeller.power_cur = 0;
        
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE)
    #undef PWM_COTROLLER_WRITE
}

void *propeller_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;

    for (;;)
    {
        pthread_mutex_lock(&info->thread.mutex.write_propeller);
        write_to_propeller(&info->propeller);
    }

    return NULL;
}

void *device_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;

    pthread_mutex_init(&info->thread.mutex.pwm_controller_reset_freq, NULL);
    pthread_mutex_lock(&info->thread.mutex.pwm_controller_reset_freq);

    for (;;)
    {
        if (pthread_mutex_trylock(&info->thread.mutex.pwm_controller_reset_freq) == 0)
        {
            pwm_controller_deinit();
            pwm_controller_init(PCA9685_ADDRESS_A000000, info->propeller.pwm_freq_calibration);
        }
    }

    return NULL;
}

int rov_device_run(struct rov_info* info)
{
    if (pwm_controller_init(PCA9685_ADDRESS_A000000, info->propeller.pwm_freq_calibration) < 0)
    {
        log_e("pwm controller init failed");
        return -1;
    }
    if (pthread_mutex_init(&info->thread.mutex.write_propeller, NULL) != 0)
    {
        log_e("cannot init propeller mutex");
        return -1;
    }

    if (pthread_create(&info->thread.tid.propeller, NULL, propeller_thread, info) != 0)
    {
        log_e("propeller thread start failed");
        return -1;
    }
    pthread_detach(info->thread.tid.propeller);

    log_i("starting thread");
    if (pthread_create(&info->thread.tid.device, NULL, device_thread, info) != 0)
    {
        log_e("thread start failed");
    }
    pthread_detach(info->thread.tid.device);

    return 0;
}

int rov_device_stop(struct rov_info* info)
{
    if (pwm_controller_deinit() < -1)
    {
        log_e("pwm controller deinit failed");
        return -1;
    }
    if (pthread_mutex_destroy(&info->thread.mutex.write_propeller) != 0)
    {
        log_e("propeller mutex destroy failed");
    }
    return 0;
}
