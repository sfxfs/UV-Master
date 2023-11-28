//
// Created by fxf on 23-9-4.
//

#ifndef CONFIG_PARAMS_DEV_CTL_H
#define CONFIG_PARAMS_DEV_CTL_H

#include <cJSON.h>

#include "../config.h"

cJSON* dev_ctl_params_add_to_root(struct dev_ctl_attr *params);
void dev_ctl_params_read_from_root(struct dev_ctl_attr *params, cJSON *node);
void dev_ctl_params_init(struct dev_ctl_attr *params);

void dev_ctl_params_all_init(struct dev_ctl_params *params);
cJSON* dev_ctl_params_write(struct dev_ctl_params *params);
void dev_ctl_params_read(struct dev_ctl_params *params, cJSON *node);

#endif //UV_MASTER_DEV_CTL_H
