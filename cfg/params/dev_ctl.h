#ifndef UVM_CFG_DEV_CTL_H
#define UVM_CFG_DEV_CTL_H

#include "cJSON.h"
#include "s2j.h"
#include "../uvm-cfg-def.h"

void dev_ctl_init_val (struct dev_ctl_params *params);
cJSON *dev_ctl_s2j (struct dev_ctl_params *params);
int dev_ctl_j2s (cJSON *json, struct dev_ctl_params *params);

#endif
