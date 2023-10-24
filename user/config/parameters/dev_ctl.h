//
// Created by fxf on 23-9-4.
//

#ifndef ROV_MASTER_DEV_CTL_H
#define ROV_MASTER_DEV_CTL_H

#include <cJSON.h>
#include "data_define.h"

cJSON* dev_ctl_params_add_to_root(pwmDev_attr_t *params);
void dev_ctl_params_read_from_root(pwmDev_attr_t *params, cJSON *node);
void dev_ctl_params_init(pwmDev_attr_t *params);

void dev_ctl_params_all_init(device_t *params);
cJSON* dev_ctl_params_write(struct rov_info* info);
void dev_ctl_params_read(struct rov_info* info, cJSON *node);

#endif //ROV_MASTER_DEV_CTL_H
