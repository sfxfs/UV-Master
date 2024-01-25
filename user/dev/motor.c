#include "motor.h"

#include <log.h>
#include <pca9685.h>

#define CALL_FOR_ALL_PROPELLER(function) \
    function(front_left) \
    function(front_right) \
    function(center_left) \
    function(center_right) \
    function(back_left) \
    function(back_right)

#define us2percent(us) (((float)(us)*100.0f)/20000.0f) // 一个周期 20 ms
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt))) //限幅函数

static int per_motor_init(propeller_attr *attr)
{
    if (attr->enabled == true)
        if (pca9685_basic_write(attr->channel, 0.0f, us2percent(PROPELLER_DUTY_MID)) != 0)
            return -1;
        else
            return 0;
    else
        if (pca9685_basic_write(attr->channel, 0.0f, 0.0f) != 0)
            return -1;
        else
            return 0;
}

int uvm_motor_init(propeller_params *cfg)
{
    log_debug("pca9685 init starting.");
    if (pca9685_basic_init(PCA9685_ADDRESS_A000000, 50 + cfg->pwm_freq_offset) != 0)
    {
        log_error("motor init failed due to pca9685.");
        return -1;
    }
    log_debug("pca9685 init finished.");
    int ret = 0;
    #define PWM_COTROLLER_WRITE(propeller) ret += per_motor_init(&cfg->propeller);
    CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    #undef PWM_COTROLLER_WRITE
    log_debug("motor init finished.");
    if (ret != 0)
    {
        log_error("one of pca9685 channel write failed.");
        pca9685_basic_deinit();
        return -2;
    }
    return 0;
}

static int per_motor_write(propeller_attr *attr, float power_percent)
{
    if (attr->enabled == true)
    {
        int16_t duty_offset = 0;
        if (power_percent != 0)
        {
            power_percent = constrain(power_percent, -attr->power_negative, attr->power_positive); // 限制最大输出
            duty_offset = PROPELLER_DUTY_OFFSET_MAX * power_percent;
            duty_offset += duty_offset > 0 ? attr->deadzone_upper : attr->deadzone_lower;
            duty_offset *= attr->reversed == true ? -1 : 1;
        }
        log_trace("powerp:%f duty_offset:%d", power_percent, duty_offset);
        log_trace("duty:%lf", us2percent(PROPELLER_DUTY_MID) + us2percent(duty_offset));
        if (pca9685_basic_write(attr->channel, 0.0f, us2percent(PROPELLER_DUTY_MID) + us2percent(duty_offset)) != 0)
            return -1;
        else
            return 0;
    }
    return 0;
}

int uvm_motor_write(propeller_params *cfg, motor_power_req req)
{
    log_debug("motor power req:%f %f %f %f %f %f", req.back_left, req.back_right, req.center_left, req.center_right, req.front_left, req.front_right);
    int ret = 0;
    #define PWM_COTROLLER_WRITE(propeller) ret += per_motor_write(&cfg->propeller, req.propeller);
    CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    #undef PWM_COTROLLER_WRITE
    if (ret != 0)
    {
        log_error("one of pca9685 channel write failed.");
        return -1;
    }
    return 0;
}
