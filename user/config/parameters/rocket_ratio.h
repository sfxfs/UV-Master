//
// Created by fxf on 9/25/23.
//

#ifndef CONFIG_PARAMS_ROCKET_RATIO_H
#define CONFIG_PARAMS_ROCKET_RATIO_H

#include <cJSON.h>

#include "../config.h"

cJSON* rocket_ratio_params_add_to_root(struct rocket_ratio_attr *params);
void rocket_ratio_params_read_from_root(struct rocket_ratio_attr *params, cJSON *node);
void rocket_ratio_params_init(struct rocket_ratio_attr *params);

void rocket_ratio_params_all_init(struct rocket_ratio_params *params);
cJSON* rocket_ratio_params_write(struct rocket_ratio_params *params);
void rocket_ratio_params_read(struct rocket_ratio_params *params, cJSON *node);

#endif //CONFIG_PARAMS_ROCKET_RATIO
