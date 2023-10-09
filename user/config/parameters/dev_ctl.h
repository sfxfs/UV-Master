//
// Created by fxf on 23-9-4.
//

#ifndef ROV_MASTER_DEV_CTL_H
#define ROV_MASTER_DEV_CTL_H

#include <cJSON.h>
#include "data_define.h"

cJSON* dev_ctl_params_add_to_root(struct pwmDev_parameters *params);
void dev_ctl_params_read_from_root(struct pwmDev_parameters *params, cJSON *node);
void dev_ctl_params_init(struct pwmDev_parameters *params);

void dev_ctl_params_all_init(dev_ctl_t *params);
cJSON* dev_ctl_params_write(struct rov_info* info);
void dev_ctl_params_read(struct rov_info* info, cJSON *node);

#endif //ROV_MASTER_DEV_CTL_H
