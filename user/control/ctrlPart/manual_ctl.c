#include "other_utils.h"

#include "manual_ctl.h"

#define CALL_FOR_ALL_PROPELLER(function) \
    function(front_left) \
    function(front_right) \
    function(center_left) \
    function(center_right) \
    function(back_left) \
    function(back_right)

/**
 * @brief 推进器参数限制
 * @param param propeller_parameters 具体推进器 propeller.which
 */
static void limit_propeller_value(propeller_attr_t *param)
{
    param->power_cur = param->power_cur * (float)param->enabled * (param->reversed == true ? -1.0f : 1.0f);

    if (param->power_cur != 0)
        param->power_cur += (float)(param->power_cur > 0 ? param->deadzone_upper : param->deadzone_lower) / 500.0f;

    param->power_cur = constrain(param->power_cur, param->power_negative, param->power_positive);
}

/**
 * @brief 各姿态运动写入（to rov_info）
 * @param info rov_info_t 结构体参数
 */
void rov_manual_control(rov_info_t *info)
{
    #define PROPELLER_VALUE_WRITE(which) \
        info->propeller.which.power_cur += info->rocket.L_UD.value * (info->rocket.L_UD.value > 0 ? info->rocket.L_UD.which.ratio_p : info->rocket.L_UD.which.ratio_n) * (info->rocket.L_UD.which.reversed == true ? -1.0f : 1.0f);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        info->propeller.which.power_cur += info->rocket.L_LR.value * (info->rocket.L_LR.value > 0 ? info->rocket.L_LR.which.ratio_p : info->rocket.L_LR.which.ratio_n) * (info->rocket.L_LR.which.reversed == true ? -1.0f : 1.0f);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        info->propeller.which.power_cur += info->rocket.R_UD.value * (info->rocket.R_UD.value > 0 ? info->rocket.R_UD.which.ratio_p : info->rocket.R_UD.which.ratio_n) * (info->rocket.R_UD.which.reversed == true ? -1.0f : 1.0f);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        info->propeller.which.power_cur += info->rocket.R_LR.value * (info->rocket.R_LR.value > 0 ? info->rocket.R_LR.which.ratio_p : info->rocket.R_LR.which.ratio_n) * (info->rocket.R_LR.which.reversed == true ? -1.0f : 1.0f);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE

    #define PROPELLER_VALUE_WRITE(which) \
        limit_propeller_value(&info->propeller.which);

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE
}

void rov_debug_control(rov_info_t *info)
{
    #define PROPELLER_VALUE_WRITE(which) \
        info->propeller.which.power_cur = (float)info->propeller.which.power_debug / 500.0f;

        CALL_FOR_ALL_PROPELLER(PROPELLER_VALUE_WRITE)
    #undef PROPELLER_VALUE_WRITE
}
