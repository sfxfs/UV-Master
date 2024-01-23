#include "ctrl.h"
#include "ctrl/mode_manual.h"
#include "dev/motor.h"

int rpc_manual_ctrl(config_data *cfg, double x, double y, double z, double r)
{
    return uvm_motor_write(cfg->propeller, uvm_manual_ctrl(cfg->rocket_ratio, x, y, z, r));
}
