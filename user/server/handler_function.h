//
// Created by fxf on 23-7-9.
//

#ifndef ROV_MASTER_HANDLER_FUNCTION_H
#define ROV_MASTER_HANDLER_FUNCTION_H

#include <cJSON.h>
#include "../data_define.h"

typedef enum move_mode
{
    rocket_ctl = 0,
    abs_ctl,    // 绝对
    rel_clt,    // 相对
} move_mode_t;

cJSON *get_rov_info     (sensor_t *sensor_data);
cJSON *get_rov_debug_info(pid_scale_t *pid);
cJSON *move_analysis    (cJSON* params, struct rov_info* info, move_mode_t mode);

#endif //ROV_MASTER_HANDLER_FUNCTION_H
