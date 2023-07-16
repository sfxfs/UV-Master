//
// Created by fxf on 23-7-9.
//

#ifndef ROV_MASTER_HANDLER_FUNCTION_H
#define ROV_MASTER_HANDLER_FUNCTION_H

#include <cJSON.h>
#include "../data_define.h"

cJSON *get_rov_info     (sensor_t *sensor_data);
cJSON *move_analysis    (cJSON* params, rocket_t* rocket, int mode);

#endif //ROV_MASTER_HANDLER_FUNCTION_H
