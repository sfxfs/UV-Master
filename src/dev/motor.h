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
    float front_right; // -1.0 ~ 1.0
    float front_left;
    float center_right;
    float center_left;
    float back_right;
    float back_left;
} motor_power_req;

int uvm_motor_init(motor_config *cfg, int16_t pwm_freq_offset);
int uvm_motor_write(motor_config *cfg, motor_power_req req);

#endif
