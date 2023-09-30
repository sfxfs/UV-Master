//
// Created by fxf on 23-9-4.
//

#include "dev_ctl.h"

cJSON* dev_ctl_params_add_to_root(struct pwmDev_parameters *params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddNumberToObject(node, "channel", params->channel);
    cJSON_AddNumberToObject(node, "pMax", params->pMax);
    cJSON_AddNumberToObject(node, "nMax", params->nMax);
    cJSON_AddNumberToObject(node, "reset", params->reset);
    cJSON_AddNumberToObject(node, "speed", params->speed);

    return node;
}

void dev_ctl_params_read_from_root(struct pwmDev_parameters *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->channel = cJSON_GetObjectItem(node, "channel")->valueint;
    params->pMax = cJSON_GetObjectItem(node, "pMax")->valueint;
    params->nMax = cJSON_GetObjectItem(node, "nMax")->valueint;
    params->reset = cJSON_GetObjectItem(node, "reset")->valueint;
    params->speed = cJSON_GetObjectItem(node, "speed")->valueint;
}

void dev_ctl_params_init(struct pwmDev_parameters *params)
{
    params->channel = 0;
    params->pMax = 1000;
    params->nMax = 0;
    params->reset = 500;
    params->speed = 50;
}
