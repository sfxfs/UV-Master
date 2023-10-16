#include "utils.h"

#include "others.h"

cJSON *server_params_add_to_root(struct server_config *params)
{
    cJSON* node = cJSON_CreateObject();

    cJSON_AddNumberToObject(node, "port", params->port);
    cJSON_AddNumberToObject(node, "timeout", params->clt_timeout);

    return node;
}

void server_params_read_from_root(struct server_config *params, cJSON *node)
{
    if (node == NULL)
        return;
    params->port = cjson_value_analysis_int(node, "port");
    params->clt_timeout = cjson_value_analysis_int(node, "timeout");
}

void server_params_init(struct server_config *params)
{
    params->port = 8888;
    params->clt_timeout = 3000;
}

void others_params_all_init(struct rov_info *params)
{
    server_params_init(&params->server);
}

cJSON *others_params_write(struct rov_info *info)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "server", server_params_add_to_root(&info->server));

    return root;
}

void others_params_read(struct rov_info *info, cJSON *node)
{
    if (node == NULL)
        return;
    server_params_read_from_root(&info->server, cJSON_GetObjectItem(node, "server"));
}
