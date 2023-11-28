//
// Created by fxf on 23-9-4.
//

#ifndef CONFIG_PARAMS_PROPELLER_H
#define CONFIG_PARAMS_PROPELLER_H

#include <cJSON.h>

#include "../config.h"

cJSON* propeller_params_add_to_root(struct propeller_attr *params);
void propeller_params_read_from_root(struct propeller_attr *params, cJSON *node);
void propeller_params_init(struct propeller_attr *params);

void propeller_params_all_init(struct propeller_params *params);
cJSON* propeller_params_write(struct propeller_params *params);
void propeller_params_read(struct propeller_params *params, cJSON *node);

#endif //CONFIG_PARAMS_PROPELLER
