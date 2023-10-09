//
// Created by fxf on 23-9-4.
//

#ifndef ROV_MASTER_PROPELLER_H
#define ROV_MASTER_PROPELLER_H

#include <cJSON.h>
#include "data_define.h"

cJSON* propeller_params_add_to_root(struct propeller_parameters *params);
void propeller_freq_read_from_root(double *freq, cJSON *node);
void propeller_params_read_from_root(struct propeller_parameters *params, cJSON *node);
void propeller_params_init_freq(double *params);
void propeller_params_init(struct propeller_parameters *params);

void propeller_params_all_init(propeller_t *params);
cJSON* propeller_params_write(struct rov_info* info);
void propeller_params_read(struct rov_info* info, cJSON *node);

#endif //ROV_MASTER_PROPELLER_H
