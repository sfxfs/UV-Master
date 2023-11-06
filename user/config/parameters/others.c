#include <stdlib.h>
#include <string.h>
#include "utils.h"

#include "others.h"

/**
 * @brief 参数转换为Cjson
 * @param params server_config 结构体参数（rovinfo中的）
 * @return Cjson object
 */
cJSON *server_params_add_to_root(struct server_config *params)
{
    cJSON* node = cJSON_CreateObject();
    if (node == NULL)
        return NULL;

    cJSON_AddStringToObject(node, "port", params->port);
    cJSON_AddNumberToObject(node, "timeout", params->clt_timeout);

    return node;
}

/**
 * @brief 读取参数（from Cjson）
 * @param params server_config 结构体参数
 * @param node Cjson
 */
void server_params_read_from_root(struct server_config *params, cJSON *node)
{
    if (node == NULL)
        return;
    char *temp = cJSON_GetObjectItem(node, "port")->valuestring;
    if (temp != NULL)
    {
        size_t size = (strlen(temp) + 1) * sizeof(char);
        params->port = malloc(size);
        memset(params->port, '\0', size);
        strcpy(params->port, temp);
    }
    params->clt_timeout = cjson_value_analysis_int(node, "timeout");
}

/**
 * @brief  server_config结构体参数初始化（掉线时间）
 * @param params server_config结构体参数（server）
 */
void server_params_init(struct server_config *params)
{
    params->port = "8888";
    params->clt_timeout = 3000;
}

/**
 * @brief 统一参数初始化
 * @param params rov_info结构体参数
 */
void others_params_all_init(struct rov_info *params)
{
    server_params_init(&params->system.server.config);
}

/**
 * @brief 统一参数写入（to Cjson）
 * @param info rov_info结构体参数
 * @return Cjson
 */
cJSON *others_params_write(struct rov_info *info)
{
    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
        return NULL;

    cJSON_AddItemToObject(root, "server", server_params_add_to_root(&info->system.server.config));

    return root;
}

/**
 * @brief 统一参数读取（From Cjson）
 * @param info 
 * @param node 
 */
void others_params_read(struct rov_info *info, cJSON *node)
{
    if (node == NULL)
        return;
    server_params_read_from_root(&info->system.server.config, cJSON_GetObjectItem(node, "server"));
}
