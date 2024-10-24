#ifndef _UVM_SRC_CTRL_MANUAL_H_
#define _UVM_SRC_CTRL_MANUAL_H_

#include "uvm_cfg.h"
#include "dev/motor.h"
#include <cfg_rocket_ratio.h>

int manual_ctrl_start_thread (config_data *cfg);
int manual_ctrl_stop_thread ();

#endif
