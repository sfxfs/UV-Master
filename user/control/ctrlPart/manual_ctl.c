#include "manual_ctl.h"

#define CALL_FOR_ALL_PROPELLER(function) \
    function(front_left) \
    function(front_right) \
    function(center_left) \
    function(center_right) \
    function(back_left) \
    function(back_right)

static void write_propeller_value(struct propeller_parameters *param, double rocket_ratio_val)
{
    param->power_cur += rocket_ratio_val * (rocket_ratio_val > 0 ? param->power_positive : param->power_negative) * param->enabled * (param->reversed == true ? -1 : 1);
}

void rov_manual_control(rov_info_t *info)
{
    #define PROPELLER_VALUE_WRITE(which) \
        write_propeller_value(&info->propeller.which, info->rocket.x * (info->rocket.x > 0 ? info->rocket.ratio_x.which.p : info->rocket.ratio_x.which.n));

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        write_propeller_value(&info->propeller.which, info->rocket.y * (info->rocket.y > 0 ? info->rocket.ratio_y.which.p : info->rocket.ratio_y.which.n));

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        write_propeller_value(&info->propeller.which, info->rocket.z * (info->rocket.z > 0 ? info->rocket.ratio_z.which.p : info->rocket.ratio_z.which.n));

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        write_propeller_value(&info->propeller.which, info->rocket.yaw * (info->rocket.yaw > 0 ? info->rocket.ratio_yaw.which.p : info->rocket.ratio_yaw.which.n));

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE
}
