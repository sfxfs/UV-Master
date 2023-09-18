#include "horizon.h"

inline double get_propeller_value(struct propeller_parameters param, double rocket_val)
{
    return rocket_val * (rocket_val > 0 ? param.power_positive : param.power_negative) * param.enabled * param.reversed;
}

void rov_horizon_control(rov_info_t *info)
{
    info->propeller.front_left.power_cur += get_propeller_value(info->propeller.front_left, info->rocket.y);
    info->propeller.front_right.power_cur += get_propeller_value(info->propeller.front_right, info->rocket.y);

    info->propeller.back_left.power_cur += get_propeller_value(info->propeller.back_left, info->rocket.y);
    info->propeller.back_right.power_cur += get_propeller_value(info->propeller.back_right, info->rocket.y);


    info->propeller.front_left.power_cur += get_propeller_value(info->propeller.front_left, info->rocket.x);
    info->propeller.front_right.power_cur -= get_propeller_value(info->propeller.front_right, info->rocket.x);

    info->propeller.back_left.power_cur -= get_propeller_value(info->propeller.back_left, info->rocket.x);
    info->propeller.back_right.power_cur += get_propeller_value(info->propeller.back_right, info->rocket.y);
}
