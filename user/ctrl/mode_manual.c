#include "mode_manual.h"
#include "log.h"

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

    if (config->x.enabled == true)
    {
        per_axis_req = per_rocket_axis(config->x, x);
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    }
    if (config->y.enabled == true)
    {
        per_axis_req = per_rocket_axis(config->y, y);
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    }
    if (config->z.enabled == true)
    {
        per_axis_req = per_rocket_axis(config->z, z);
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    }
    if (config->r.enabled == true)
    {
        per_axis_req = per_rocket_axis(config->r, r);
        CALL_FOR_ALL_PROPELLER(PWM_COTROLLER_WRITE);
    }

    #undef PWM_COTROLLER_WRITE
    return req;
}
