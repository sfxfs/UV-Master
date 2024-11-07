#include "control.h"

#include "ctrl/mode_manual.h"
#include "dev/motor.h"
#include "log.h"

rocket_raw_t g_rocket_raw;

void rpc_manual_ctrl(config_data *cfg, double x, double y, double z, double r)
{
    log_debug("manual ctrl cmd recv: |[x]%lf|[y]%lf|[z]%lf|[r]%lf|", x, y, z, r);
    if (g_rocket_raw.x != x || g_rocket_raw.y != y || g_rocket_raw.z != z || g_rocket_raw.rot != r)
        g_rocket_raw.updated = true;
    g_rocket_raw.x = x;
    g_rocket_raw.y = y;
    g_rocket_raw.z = z;
    g_rocket_raw.rot = r;
}

void catch_ctrl(double val)
{
    log_debug("catch:%lf", val); // RB pressing down is 1(RT is -1), release is 0
    g_rocket_raw.catch = (catch_stat_t)val;
}
