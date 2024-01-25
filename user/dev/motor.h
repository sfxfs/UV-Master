#ifndef _UVM_SRC_DEV_MOTOR_H_
#define _UVM_SRC_DEV_MOTOR_H_

#include <cfg_propeller.h>

#define PROPELLER_DUTY_MID 1500 // us
#define PROPELLER_DUTY_OFFSET_MAX 500 // us

typedef struct
{
    float front_right; // -1.0 ~ 1.0
    float front_left;
    float center_right;
    float center_left;
    float back_right;
    float back_left;
} motor_power_req;

int uvm_motor_init(propeller_params *cfg);
int uvm_motor_write(propeller_params *cfg, motor_power_req req);

#endif
