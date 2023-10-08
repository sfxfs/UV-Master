//
// Created by fxf on 23-9-3.
//

#ifndef ROV_MASTER_CONFIG_H
#define ROV_MASTER_CONFIG_H

#include <cJSON.h>
#include "data_define.h"

int rov_config_init(struct rov_info* info);

int rov_config_write_json_to_file(cJSON *params);
int rov_config_write_to_file(struct rov_info* info);

cJSON *rov_config_read_from_file_return_cjson(void);
int rov_config_read_from_file(struct rov_info* info);

#endif //ROV_MASTER_CONFIG_H
