#ifndef _UVM_SRC_DEV_MOTOR_H_
#define _UVM_SRC_DEV_MOTOR_H_

#include <params/propeller.h>

typedef struct
{
    propeller_attr front_right;
    propeller_attr front_left;
    propeller_attr center_right;
    propeller_attr center_left;
    propeller_attr back_right;
    propeller_attr back_left;
} motor_config;

typedef struct
{
    float front_right_power_persent;
    float front_left_power_persent;
    float center_right_power_persent;
    float center_left_power_persent;
    float back_right_power_persent;
    float back_left_power_persent;
} motor_power_req;


#endif
