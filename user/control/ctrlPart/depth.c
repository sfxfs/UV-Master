#include "depth.h"

inline double get_propeller_value(struct propeller_parameters param, double rocket_val)
{
    return rocket_val * (rocket_val > 0 ? param.power_positive : param.power_negative) * param.enabled * param.reversed;
}

void rov_depth_control(rov_info_t *info)
{
    info->propeller.center_left.power_cur += get_propeller_value(info->propeller.center_left, info->rocket.z);

    info->propeller.center_right.power_cur += get_propeller_value(info->propeller.center_right, info->rocket.z);
}
