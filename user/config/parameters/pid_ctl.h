//
// Created by fxf on 23-9-4.
//

#ifndef ROV_MASTER_PID_CTL_H
#define ROV_MASTER_PID_CTL_H

#include <cJSON.h>
#include "data_define.h"

cJSON* pid_ctl_params_add_to_root(struct pid_scale_parameters *params);
void pid_ctl_params_read_from_root(struct pid_scale_parameters *params, cJSON *node);
void pid_ctl_params_init(struct pid_scale_parameters *params);

cJSON* pid_ctl_params_write(struct rov_info* info);
void pid_ctl_params_read(struct rov_info* info, cJSON *node);

#endif //ROV_MASTER_PID_CTL_H
