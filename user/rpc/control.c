#include "control.h"

#include "ctrl/mode_manual.h"
#include "dev/motor.h"
#include "log.h"

rocket_raw_t g_rocket_raw;

void rpc_manual_ctrl(config_data *cfg, double x, double y, double z, double r)
{
    log_debug("manual ctrl cmd recv: |[x]%lf|[y]%lf|[z]%lf|[r]%lf|", x, y, z, r);
    g_rocket_raw.x = x;
    g_rocket_raw.y = y;
    g_rocket_raw.z = z;
    g_rocket_raw.rot = r;
    g_rocket_raw.updated = true;
}
