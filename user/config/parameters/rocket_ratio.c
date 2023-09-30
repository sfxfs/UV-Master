//
// Created by fxf on 9/25/23.
//

#include "rocket_ratio.h"

static cJSON* _rocket_dir_add_to_root(struct power_dir params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddItemToObject(node, "reversed", params.reversed == 1 ? cJSON_CreateTrue() : cJSON_CreateFalse());
    cJSON_AddNumberToObject(node, "p", params.p);
    cJSON_AddNumberToObject(node, "n", params.n);

    return node;
}

static void _rocket_dir_read_from_root(struct power_dir *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->reversed = cJSON_GetObjectItem(node, "reversed")->valueint;
    params->p = cJSON_GetObjectItem(node, "p")->valuedouble;
    params->n = cJSON_GetObjectItem(node, "n")->valuedouble;
}

static void _rocket_dir_params_init(struct power_dir *params)
{
    params->p = 0.5;
    params->n = 0.5;
}

cJSON* rocket_ratio_params_add_to_root(struct r2p_ratio *params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddItemToObject(node, "front_right", _rocket_dir_add_to_root(params->front_right));
    cJSON_AddItemToObject(node, "front_left", _rocket_dir_add_to_root(params->front_left));
    cJSON_AddItemToObject(node, "center_right", _rocket_dir_add_to_root(params->center_right));
    cJSON_AddItemToObject(node, "center_left", _rocket_dir_add_to_root(params->center_left));
    cJSON_AddItemToObject(node, "back_right", _rocket_dir_add_to_root(params->back_right));
    cJSON_AddItemToObject(node, "back_left", _rocket_dir_add_to_root(params->back_left));

    return node;
}

void rocket_ratio_params_read_from_root(struct r2p_ratio *params, cJSON *node)
{
    if (node == NULL)
        return;
    _rocket_dir_read_from_root(&params->front_right, cJSON_GetObjectItem(node, "front_right"));
    _rocket_dir_read_from_root(&params->front_left, cJSON_GetObjectItem(node, "front_left"));
    _rocket_dir_read_from_root(&params->center_right, cJSON_GetObjectItem(node, "center_right"));
    _rocket_dir_read_from_root(&params->center_left, cJSON_GetObjectItem(node, "center_left"));
    _rocket_dir_read_from_root(&params->back_right, cJSON_GetObjectItem(node, "back_right"));
    _rocket_dir_read_from_root(&params->back_left, cJSON_GetObjectItem(node, "back_left"));
}

void rocket_ratio_params_init(struct r2p_ratio *params)
{
    _rocket_dir_params_init(&params->front_right);
    _rocket_dir_params_init(&params->front_left);
    _rocket_dir_params_init(&params->center_right);
    _rocket_dir_params_init(&params->center_left);
    _rocket_dir_params_init(&params->back_right);
    _rocket_dir_params_init(&params->back_left);
}
