//
// Created by fxf on 9/25/23.
//

#ifndef ROV_MASTER_ROCKET_RATIO_H
#define ROV_MASTER_ROCKET_RATIO_H

#include <cJSON.h>
#include "../../data_define.h"

cJSON* rocket_ratio_params_add_to_root(struct r2p_ratio *params);
void rocket_ratio_params_read_from_root(struct r2p_ratio *params, cJSON *node);
void rocket_ratio_params_init(struct r2p_ratio *params);

#endif //ROV_MASTER_ROCKET_RATIO_H
