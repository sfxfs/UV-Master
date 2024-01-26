#include "control.h"

#include "ctrl/mode_manual.h"
#include "dev/motor.h"
#include "log.h"

int rpc_manual_ctrl(config_data *cfg, double x, double y, double z, double r)
{
    log_debug("manual ctrl cmd recv: x|%lf y|%lf z|%lf r|%lf", x, y, z, r);
    return uvm_motor_write(cfg->propeller, uvm_manual_ctrl(cfg->rocket_ratio, x, y, z, r));
}
