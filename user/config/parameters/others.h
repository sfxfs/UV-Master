#ifndef CONFIG_PARAMS_OTHERS
#define CONFIG_PARAMS_OTHERS

#include <cJSON.h>
#include "data_define.h"

cJSON *server_params_add_to_root(struct server_config *params);
void server_params_read_from_root(struct server_config *params, cJSON *node);
void server_params_init(struct server_config *params);

void others_params_all_init(struct rov_info *params);
cJSON *others_params_write(struct rov_info *info);
void others_params_read(struct rov_info *info, cJSON *node);

#endif
