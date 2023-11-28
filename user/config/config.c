//
// Created by fxf on 23-9-3.
//

#define LOG_TAG "config.main"

#include "config.h"

#include <elog.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parameters/others.h"
#include "parameters/dev_ctl.h"
#include "parameters/propeller.h"
#include "parameters/rocket_ratio.h"

/**
 * @brief rov信息初始化
 * @param info rov_info结构体参数
 */
static void uv_info_initial_value(uv_config_t *handle)
{
    propeller_params_all_init(&handle->data.propeller);
    rocket_ratio_params_all_init(&handle->data.rocket_ratio);
    dev_ctl_params_all_init(&handle->data.dev_ctl);
    others_params_all_init(&handle->data.others);
}

/**
 * @brief 由 cJSON 链表写入配置到config文件
 * @param params json 类型配置数据
 * @return 0：成功  -1：失败
 */
static int write_config_file(const char *config_file_path, cJSON *params)
{
    char *temp = cJSON_Print(params);
    if (temp == NULL)
    {
        log_e("cjson print error, invaild cjson data");
        return -1;
    }
    FILE *fp = fopen(config_file_path, "w");
    if (fp == NULL)
    {
        //使用“写入”方式创建文件
        fp = fopen(config_file_path, "wt+");
        if(fp == NULL)
        {
            log_e("error in creating config file");
            free(temp);
            return -1;
        }
    }
    int flen = fputs(temp, fp);
    if (flen < 0)   //写入文件
    {
        log_e("error in fputs config file");
        fclose(fp);
        free(temp);
        return -1;
    }
    log_i("write %d bytes to config file", flen);

    fclose(fp);
    free(temp);
    return 0;
}

/**
 * @brief rov外设配置信息写入config.
 * @param info rov_info结构体参数
 * @return 0：成功  -1：失败
 */
int uv_config_write(uv_config_t *handle)
{
    cJSON* params = cJSON_CreateObject();

    cJSON_AddItemToObject(params, "propeller_params", propeller_params_write(&handle->data.propeller));
    cJSON_AddItemToObject(params, "dev_ctl_params", dev_ctl_params_write(&handle->data.dev_ctl));
    cJSON_AddItemToObject(params, "rocket_ratio_params", rocket_ratio_params_write(&handle->data.rocket_ratio));
    cJSON_AddItemToObject(params, "others_config_params", others_params_write(&handle->data.others));

    if (write_config_file(handle->file_path, params) != 0)
    {
        cJSON_Delete(params);
        return -1;
    }

    cJSON_Delete(params);
    return 0;
}

/**
 * @brief 读取配置文件（记得用完要 delete）
 * @return 由读取到的配置文件创建的 cjson 结构体
 */
static cJSON *read_config_file(const char *config_file_path)
{
    FILE *fp = fopen(config_file_path, "r");
    if (fp == NULL)
    {
        log_e("file no exist");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    const int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buf = calloc(file_size + 1, sizeof(char));
    size_t read_byte = fread(buf, sizeof(char), file_size, fp);
    if (fclose(fp) != 0)
    {
        log_e("cannot close config file");
    }
    log_i("read %d bytes of config file", read_byte);
    if (file_size != read_byte)
    {
        log_e("config file read incomplete");
        free(buf);
        return NULL;
    }

    buf[file_size] = '\0';
    cJSON * json_return = cJSON_Parse(buf);
    free(buf);

    return json_return;
}

/**
 * @brief rov外设配置信息读取（From config.json to Rov_info）
 * @param info rov_info结构体参数
 * @return 0：成功 -1：失败
 */
int uv_config_read(uv_config_t *handle)
{
    cJSON *params = read_config_file(handle->file_path);
    if (params != NULL) // 非空，解析
    {
        propeller_params_read(&handle->data.propeller, cJSON_GetObjectItem(params, "propeller_params"));
        dev_ctl_params_read(&handle->data.dev_ctl, cJSON_GetObjectItem(params, "dev_ctl_params"));
        rocket_ratio_params_read(&handle->data.rocket_ratio, cJSON_GetObjectItem(params, "rocket_ratio_params"));
        others_params_read(&handle->data.others, cJSON_GetObjectItem(params, "others_config_params"));
        cJSON_Delete(params);
    }
    else
    {
        log_e("config file parse error");
        return -1;
    }

    return 0;
}

/**
 * @brief rov外设配置信息初始化
 * @param info rov_info结构体参数
 * @return 0：成功 -1：失败
 */
uv_config_t *uv_config_init(const char *config_file_path)
{
    log_i("load to config file");
    uv_config_t *handle_return = calloc(1, sizeof(uv_config_t));
    if (handle_return == NULL)
    {
        log_e("cannot alloc mem for config data");
        return NULL;
    }

    if (0 == access(config_file_path, F_OK)) // 0:存在
    {
        if (uv_config_read(handle_return) < 0)  //能够读取则不做任何事
        {
            log_e("cannot read config file");
            free(handle_return);
            return NULL;
        }
    }
    else
    {
        log_w("config file not exist, create it");
        uv_info_initial_value(handle_return); //初始化Rov_info
        if (uv_config_write(handle_return) < 0) //创建并将Rov_info信息写至config
        {
            log_e("cannot write config file");
            free(handle_return);
            return NULL;
        }
    }

    handle_return->file_path = strdup(config_file_path);

    return handle_return;
}
