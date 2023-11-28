#ifndef CONFIG_PARAMS_OTHERS_H
#define CONFIG_PARAMS_OTHERS_H

#include <cJSON.h>

#include "../config.h"

cJSON *server_params_add_to_root(struct server_attr *params);
void server_params_read_from_root(struct server_attr *params, cJSON *node);
void server_params_init(struct server_attr *params);

void others_params_all_init(struct others_config_params *params);
cJSON *others_params_write(struct others_config_params *params);
void others_params_read(struct others_config_params *params, cJSON *node);

#endif
