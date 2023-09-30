//
// Created by fxf on 23-9-4.
//

#include "propeller.h"

cJSON* propeller_params_add_to_root(struct propeller_parameters *params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddItemToObject(node, "reversed", params->reversed == 1 ? cJSON_CreateTrue() : cJSON_CreateFalse());
    cJSON_AddItemToObject(node, "enabled", params->enabled == 1 ? cJSON_CreateTrue() : cJSON_CreateFalse());
    cJSON_AddNumberToObject(node, "channel", params->channel);
    cJSON_AddNumberToObject(node, "deadzone_lower", params->deadzone_lower);
    cJSON_AddNumberToObject(node, "deadzone_upper", params->deadzone_upper);
    cJSON_AddNumberToObject(node, "power_positive", params->power_positive);
    cJSON_AddNumberToObject(node, "power_negative", params->power_negative);

    return node;
}

void propeller_params_read_from_root(struct propeller_parameters *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->reversed =  cJSON_GetObjectItem(node, "reversed")->valueint;
    params->enabled =  cJSON_GetObjectItem(node, "enabled")->valueint;
    params->channel = cJSON_GetObjectItem(node, "channel")->valueint;
    params->power_positive = cJSON_GetObjectItem(node, "power_positive")->valuedouble;
    params->power_negative = cJSON_GetObjectItem(node, "power_negative")->valuedouble;
    params->deadzone_upper = cJSON_GetObjectItem(node, "deadzone_upper")->valuedouble;
    params->deadzone_lower = cJSON_GetObjectItem(node, "deadzone_lower")->valuedouble;
}

void propeller_params_init_freq(double *params)
{
    *params = 50;
}

void propeller_params_init(struct propeller_parameters *params)
{
    if (params == NULL)
        return;
    params->enabled = 1;
    params->reversed = 0;
    params->channel = 0;
    params->deadzone_upper = 0;
    params->deadzone_lower = 0;
    params->power_positive = 0.1;
    params->power_negative = 0.1;
}
