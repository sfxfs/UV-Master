//
// Created by fxf on 23-9-3.
//

#define LOG_TAG "config.main"

#include <elog.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parameters/others.h"
#include "parameters/pid_ctl.h"
#include "parameters/dev_ctl.h"
#include "parameters/propeller.h"
#include "parameters/rocket_ratio.h"

#include "config.h"

#define CONFIG_FILE_PATH "config.json"
#define CONFIG_FILE_LEN 4096

/**
 * @brief rov信息初始化
 * @param info rov_info结构体参数
 */
static void rov_info_write_initial_value(struct rov_info* info)
{
    memset(info, 0, sizeof(rov_info_t));//变量初始化

    propeller_params_all_init(&info->propeller);
    rocket_ratio_params_all_init(&info->rocket);
    pid_ctl_params_all_init(&info->pidScale);
    dev_ctl_params_all_init(&info->devCtl);
    others_params_all_init(info);
}

/**
 * @brief 由 cJSON 链表写入配置到config文件
 * @param params json 类型配置数据
 * @return 0：成功  -1：失败
 */
int rov_config_write_json_to_file(cJSON *params)
{
    char *temp = cJSON_Print(params);
    if (temp == NULL)
    {
        log_e("cjson print error, invaild cjson data");
        return -1;
    }
    FILE *fp = fopen(CONFIG_FILE_PATH, "w");
    if (fp == NULL)
    {
        //使用“写入”方式创建文件
        fp = fopen(CONFIG_FILE_PATH, "wt+");
        if(fp == NULL)
        {
            log_e("error in creating config file");
            free(temp);
            return -1;
        }
    }
    if (fputs(temp, fp) < 0)   //写入文件
    {
        log_e("error in fputs config file");
        fclose(fp);
        free(temp);
        return -1;
    }

    fclose(fp);
    free(temp);
    return 0;
}

/**
 * @brief rov外设配置信息写入config.
 * @param info rov_info结构体参数
 * @return 0：成功  -1：失败
 */
int rov_config_write_to_file(struct rov_info* info)
{
    cJSON* params = cJSON_CreateObject();

    cJSON_AddItemToObject(params, "propeller_params", propeller_params_write(info));
    cJSON_AddItemToObject(params, "pid_clt_params", pid_ctl_params_write(info));
    cJSON_AddItemToObject(params, "dev_ctl_params", dev_ctl_params_write(info));
    cJSON_AddItemToObject(params, "rocket_ratio_params", rocket_ratio_params_write(info));
    cJSON_AddItemToObject(params, "others_config_params", others_params_write(info));

    if (rov_config_write_json_to_file(params) != 0)
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
cJSON *rov_config_read_from_file_return_cjson()
{
    FILE *fp = fopen(CONFIG_FILE_PATH, "r");
    if (fp == NULL)
    {
        log_e("file no exist");
        return NULL;
    }

    char buf[CONFIG_FILE_LEN] = {0};
    size_t read_byte = fread(buf, 1, CONFIG_FILE_LEN, fp);
    if (fclose(fp) != 0)
        log_e("cannot close file");
    log_i("read %d bytes of config file", read_byte);
    if (CONFIG_FILE_LEN == read_byte) //文件内容>=4096字节
    {
        log_e("size of config file beyond the max len");
        return NULL;
    }

    return cJSON_Parse(buf);
}

/**
 * @brief rov外设配置信息读取（From config.json to Rov_info）
 * @param info rov_info结构体参数
 * @return 0：成功 -1：失败
 */
int rov_config_read_from_file(struct rov_info* info)
{
    cJSON *params = rov_config_read_from_file_return_cjson();
    if (params != NULL) // propeller_parameters 非空，解析
    {
        propeller_params_read(info, cJSON_GetObjectItem(params, "propeller_params"));
        pid_ctl_params_read(info, cJSON_GetObjectItem(params, "pid_clt_params"));
        dev_ctl_params_read(info, cJSON_GetObjectItem(params, "dev_params"));
        rocket_ratio_params_read(info, cJSON_GetObjectItem(params, "rocket_ratio_params"));
        others_params_read(info, cJSON_GetObjectItem(params, "others_config_params"));
    }
    else
    {
        log_e("config file parse error");
        return -1;
    }

    cJSON_Delete(params);
    return 0;
}

/**
 * @brief rov外设配置信息初始化
 * @param info rov_info结构体参数
 * @return 0：成功 -1：失败
 */
int rov_config_init(struct rov_info* info)
{
    log_i("load to config file");
    if (0 == access(CONFIG_FILE_PATH, F_OK)) // 0:存在
    {
        if (rov_config_read_from_file(info) < 0)  //能够读取则不做任何事
        {
            log_e("cannot read config file");
            return -1;
        }
    }
    else
    {
        log_w("config file not exist, create it");
        rov_info_write_initial_value(info); //初始化Rov_info
        if (rov_config_write_to_file(info) < 0) //创建并将Rov_info信息写至config
        {
            log_e("cannot write config file");
            return -1;
        }
    }
    return 0;
}
