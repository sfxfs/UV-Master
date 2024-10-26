#include "catcher.h"

#include "log.h"
#include "pca9685.h"

static int cur;

#define us2percent(us) (((us) * 100.0) / 20000.0)                                             // 一个周期 20 ms
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt))) // 限幅函数

int uvm_catcher_init(dev_ctl_attr *cfg)
{
    if (cfg->enabled != true)
        return -1;
    cur = cfg->reset;

    if (pca9685_basic_write(cfg->channel, 0.0f, us2percent(cfg->reset)) != 0)
        return -1;
    else
        return 0;
}

int uvm_catcher_deinit(dev_ctl_attr *cfg)
{
    if (cfg->enabled != true)
        return -1;
    if (pca9685_basic_write(cfg->channel, 0.0f, 0.0f) != 0)
        return -1;
    else
        return 0;
}

int uvm_catcher_write(dev_ctl_attr *cfg, int req)
{
    if (cfg->enabled != true)
        return -1;
    cur = constrain(cur + (req * cfg->step), cfg->nMax, cfg->pMax);
    log_debug("catcher cur:%d", cur);
    if (pca9685_basic_write(cfg->channel, 0.0f, us2percent(cur)) != 0)
        return -1;
    else
        return 0;
}
