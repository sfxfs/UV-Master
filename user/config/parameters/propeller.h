//
// Created by fxf on 23-9-4.
//

#ifndef ROV_MASTER_PROPELLER_H
#define ROV_MASTER_PROPELLER_H

#include <cJSON.h>
#include "data_define.h"

cJSON* propeller_params_add_to_root(propeller_attr_t *params);
void propeller_freq_read_from_root(uint16_t *freq, cJSON *node);
void propeller_params_read_from_root(propeller_attr_t *params, cJSON *node);
void propeller_params_init_freq(uint16_t *params);
void propeller_params_init(propeller_attr_t *params);

void propeller_params_all_init(propeller_t *params);
cJSON* propeller_params_write(struct rov_info* info);
void propeller_params_read(struct rov_info* info, cJSON *node);

#endif //ROV_MASTER_PROPELLER_H
