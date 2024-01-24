#ifndef _UVM_SRC_CTRL_MANUAL_H_
#define _UVM_SRC_CTRL_MANUAL_H_

#include <motor.h>
#include <cfg_rocket_ratio.h>

motor_power_req uvm_manual_ctrl(rocket_ratio_params *config, double x, double y, double z, double r);

#endif
