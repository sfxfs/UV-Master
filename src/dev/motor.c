#include "motor.h"

#include <log/log.h>
#include <driver_pca9685_basic.h>

#define CALL_FOR_ALL_PROPELLER(function) \
    function(front_left) \
    function(front_right) \
    function(center_left) \
    function(center_right) \
    function(back_left) \
    function(back_right)

#define us2percent(us) (((float)us)/20000.0f)*100.0f // 一个周期 20 ms
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

int uvm_motor_init(motor_config *cfg, int16_t pwm_freq_offset)
{
    if (pca9685_basic_init(PCA9685_ADDRESS_A000000, 50 + pwm_freq_offset) != 0)
    {
        log_error("pca9685 init failed.");
        return -1;
    }
    int ret = 0;
    #define PWM_COTROLLER_WRITE(propeller) ret += per_motor_init(&cfg->propeller);
    CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    #undef PWM_COTROLLER_WRITE
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
        if (power_percent != 0)
        {
            power_percent = power_percent + us2percent(power_percent > 0 ? attr->deadzone_upper : attr->deadzone_lower); // 加入死区偏移
            power_percent = power_percent * attr->reversed == true ? -1 : 1; // 是否反转
            power_percent = constrain(power_percent, attr->power_negative, attr->power_positive); // 限制最大输出
        }
        if (pca9685_basic_write(attr->channel, 0.0f, power_percent) != 0)
            return -1;
        else
            return 0;
    }
    return 0;
}

int uvm_motor_write(motor_config *cfg, motor_power_req req)
{
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
