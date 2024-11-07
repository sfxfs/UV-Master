#include "mode_manual.h"
#include <pthread.h>
#include "log.h"
#include "dev/catcher.h"
#include "dev/motor.h"
#include <cfg_rocket_ratio.h>
#include "rpc/control.h"
#include "utils/delay.h"

#define CALL_FOR_ALL_PROPELLER(function) \
    function(front_left) \
    function(front_right) \
    function(center_left) \
    function(center_right) \
    function(back_left) \
    function(back_right)

static float per_motor(rocket_ratio_propeller_attr config, double axis)
{
    if (axis == 0)
        return 0;
    float motor_power_percent = 0;

    if (config.enabled == true)
    {
        motor_power_percent = axis * (axis > 0 ? config.ratio_p : config.ratio_n); // 乘以功率系数
        motor_power_percent = motor_power_percent * (config.reversed == true ? -1.0f : 1.0f); // 是否反转
    }
    return motor_power_percent;
}

static motor_power_req per_rocket_axis(rocket_ratio_axis_attr config, double axis)
{
    motor_power_req per_axis = {0};
    #define PWM_COTROLLER_WRITE(propeller) per_axis.propeller = per_motor(config.propeller, axis);
    CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    #undef PWM_COTROLLER_WRITE
    return per_axis;
}

motor_power_req uvm_manual_ctrl(rocket_ratio_params *config, double x, double y, double z, double r)
{
    motor_power_req req = {0};
    motor_power_req per_axis_req;

    #define PWM_COTROLLER_WRITE(propeller) \
        req.propeller += per_axis_req.propeller;

    if (config->x.enabled == true && (x >= config->x.deadzone_p || x <= config->x.deadzone_n))
    {
        per_axis_req = per_rocket_axis(config->x, x);
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    }
    if (config->y.enabled == true && (y >= config->y.deadzone_p || y <= config->y.deadzone_n))
    {
        per_axis_req = per_rocket_axis(config->y, y);
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    }
    if (config->z.enabled == true && (z >= config->z.deadzone_p || z <= config->z.deadzone_n))
    {
        per_axis_req = per_rocket_axis(config->z, z);
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    }
    if (config->r.enabled == true && (r >= config->r.deadzone_p || r <= config->r.deadzone_n))
    {
        per_axis_req = per_rocket_axis(config->r, r);
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    }

    #undef PWM_COTROLLER_WRITE
    return req;
}

extern rocket_raw_t g_rocket_raw;

static void *manual_ctrl_thread(void *arg)
{
    config_data *cfg = (config_data *)arg;
    for(;;)
    {
        uvm_delay(20);
        if (g_rocket_raw.updated)
        {
            g_rocket_raw.updated = false;
            uvm_motor_write(cfg->propeller, uvm_manual_ctrl(cfg->rocket_ratio,
                                                            g_rocket_raw.x,
                                                            g_rocket_raw.y,
                                                            g_rocket_raw.z,
                                                            g_rocket_raw.rot));
        }
        if (g_rocket_raw.catch != CATCH_NOACT)
        {
            uvm_catcher_write(&cfg->dev_ctl->arm_attr, g_rocket_raw.catch);
        }
    }
    return NULL;
}

pthread_t manual_ctrl_tid;

int manual_ctrl_start_thread (config_data *cfg)
{
    if (pthread_create(&manual_ctrl_tid, NULL, manual_ctrl_thread, cfg) != 0)
    {
        log_error("Thread start failed.");
        return -1;
    }
    pthread_detach(manual_ctrl_tid);
    return 0;
}

int manual_ctrl_stop_thread ()
{
    return pthread_cancel(manual_ctrl_tid);
}
