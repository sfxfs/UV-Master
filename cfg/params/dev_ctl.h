#ifndef UVM_CFG_DEV_CTL_H
#define UVM_CFG_DEV_CTL_H

#include "cJSON.h"
#include "s2j.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    bool enabled;
    int16_t channel;
    uint16_t pMax;
    uint16_t nMax;
    uint16_t reset;
    int16_t step;
} dev_ctl_attr;

typedef struct
{
    dev_ctl_attr arm_attr;
    dev_ctl_attr light_attr;
} dev_ctl_params;

dev_ctl_params *dev_ctl_create_with_init_val (void);
cJSON *dev_ctl_s2j (dev_ctl_params *params);
dev_ctl_params *dev_ctl_j2s (cJSON *json);

#endif
