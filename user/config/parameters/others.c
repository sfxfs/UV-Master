#include "utils.h"

#include "others.h"

/**
 * @brief 参数转换为Cjson
 * @param params server_config 结构体参数（rovinfo中的）
 * @return Cjson object
 */
cJSON *server_params_add_to_root(struct server_attr *params)
{
    cJSON* node = cJSON_CreateObject();
    if (node == NULL)
        return NULL;

    cJSON_AddNumberToObject(node, "port", params->port);
    cJSON_AddNumberToObject(node, "timeout", params->timeout);

    return node;
}

/**
 * @brief 读取参数（from Cjson）
 * @param params server_config 结构体参数
 * @param node Cjson
 */
void server_params_read_from_root(struct server_attr *params, cJSON *node)
{
    if (node == NULL)
        return;

    params->port = cjson_value_analysis_int(node, "port");
    params->timeout = cjson_value_analysis_int(node, "timeout");
}

/**
 * @brief  server_config结构体参数初始化（掉线时间）
 * @param params server_config结构体参数（server）
 */
void server_params_init(struct server_attr *params)
{
    params->port = 8888;
    params->timeout = 3000;
}

/**
 * @brief 统一参数初始化
 * @param params rov_info结构体参数
 */
void others_params_all_init(struct others_config_params *params)
{
    server_params_init(&params->server_attr);
}

/**
 * @brief 统一参数写入（to Cjson）
 * @param info rov_info结构体参数
 * @return Cjson
 */
cJSON *others_params_write(struct others_config_params *params)
{
    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
        return NULL;

    cJSON_AddItemToObject(root, "server", server_params_add_to_root(&params->server_attr));

    return root;
}

/**
 * @brief 统一参数读取（From Cjson）
 * @param info 
 * @param node 
 */
void others_params_read(struct others_config_params *params, cJSON *node)
{
    if (node == NULL)
        return;

    server_params_read_from_root(&params->server_attr, cJSON_GetObjectItem(node, "server"));
}
