//
// Created by fxf on 23-8-29.
//

#define LOG_TAG "device.main"

#include <elog.h>
#include <unistd.h>
#include <pthread.h>
#include "other_utils.h"

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

/**
 * @brief 推进器输出
 * @param param propeller_t 结构体参数
 */
static void write_to_propeller(propeller_t *param)
{
    #define PWM_COTROLLER_WRITE(propeller) \
        pwm_controller_write(param->propeller.channel, 0.0f, 7.5f + constrain(2.5f * param->propeller.power_cur, -2.5f, 2.5f));\
        param->propeller.power_last = param->propeller.power_cur;\
        param->propeller.power_cur = 0;

        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE)
    #undef PWM_COTROLLER_WRITE
}

/**
 * @brief 推进器线程
 * @param arg 控制参数信息，void * (rov_info_t)
 * @return NULL
 */
void *propeller_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;

    for (int i = 0; i < 16; i++)
        pwm_controller_write(i, 0, 0);

    for (;;)
    {
        pthread_mutex_lock(&info->system.device.power_output_mtx);
        write_to_propeller(&info->propeller);
        pthread_mutex_unlock(&info->system.device.power_output_mtx);
    }

    return NULL;
}

/**
 * @brief 推进器启动
 * @param info rov_info结构体参数
 * @return 0:成功 -1：失败
 */
int rov_device_run(struct rov_info* info)
{
    pthread_mutex_init(&info->system.device.power_output_mtx, NULL);

    log_i("starting pwm controller");
    if (pwm_controller_init(PCA9685_ADDRESS_A000000, info->propeller.pwm_freq_calibration) < 0)
    {
        log_e("pwm controller init failed");
        return -1;
    }

    if (pthread_create(&info->system.device.main_tid, NULL, propeller_thread, info) != 0)
    {
        log_e("propeller thread start failed");
        return -1;
    }
    pthread_detach(info->system.device.main_tid);

    return 0;
}

/**
 * @brief 取消推进器控制
 * @param info rov_info结构体参数
 * @return 0：成功 -1：失败
 */
int rov_device_stop(struct rov_info* info)
{
    if (pwm_controller_deinit() < -1)
    {
        log_e("pwm controller deinit failed");
        return -1;
    }
    return 0;
}
