#include "other.h"

#include "manual_ctl.h"

#define CALL_FOR_ALL_PROPELLER(function) \
    function(front_left) \
    function(front_right) \
    function(center_left) \
    function(center_right) \
    function(back_left) \
    function(back_right)

static void limit_propeller_value(struct propeller_parameters *param)
{
    param->power_cur = param->power_cur * (float)param->enabled * (param->reversed == true ? -1.0f : 1.0f);

    if (param->power_cur != 0)
        param->power_cur += (float)(param->power_cur > 0 ? param->deadzone_upper : param->deadzone_lower) / 500.0f;

    param->power_cur = constrain(param->power_cur, param->deadzone_lower, param->deadzone_upper);
}

void rov_manual_control(rov_info_t *info)
{
    #define PROPELLER_VALUE_WRITE(which) \
        info->propeller.which.power_cur += info->rocket.x * (info->rocket.x > 0 ? info->rocket.ratio_x.which.p : info->rocket.ratio_x.which.n) * (info->rocket.ratio_x.which.reversed == true ? -1.0f : 1.0f);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        info->propeller.which.power_cur += info->rocket.y * (info->rocket.y > 0 ? info->rocket.ratio_y.which.p : info->rocket.ratio_y.which.n) * (info->rocket.ratio_y.which.reversed == true ? -1.0f : 1.0f);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        info->propeller.which.power_cur += info->rocket.z * (info->rocket.z > 0 ? info->rocket.ratio_z.which.p : info->rocket.ratio_z.which.n) * (info->rocket.ratio_z.which.reversed == true ? -1.0f : 1.0f);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        info->propeller.which.power_cur += info->rocket.yaw * (info->rocket.yaw > 0 ? info->rocket.ratio_yaw.which.p : info->rocket.ratio_yaw.which.n) * (info->rocket.ratio_yaw.which.reversed == true ? -1.0f : 1.0f);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        limit_propeller_value(&info->propeller.which);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE
}
