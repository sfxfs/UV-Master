//
// Created by fxf on 23-9-4.
//

#include "pid_ctl.h"

cJSON* pid_ctl_params_add_to_root(struct pid_scale_parameters *params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddNumberToObject(node, "p", params->Kp);
    cJSON_AddNumberToObject(node, "i", params->Ki);
    cJSON_AddNumberToObject(node, "d", params->Kd);

    return node;
}

void pid_ctl_params_read_from_root(struct pid_scale_parameters *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->Kp = (float)cJSON_GetObjectItem(node, "p")->valuedouble;
    params->Ki = (float)cJSON_GetObjectItem(node, "i")->valuedouble;
    params->Kd = (float)cJSON_GetObjectItem(node, "d")->valuedouble;
}

void pid_ctl_params_init(struct pid_scale_parameters *params)
{
    if (params == NULL)
        return;
    params->Kp = 0.1f;
    params->Ki = 0;
    params->Kd = 0;
}
