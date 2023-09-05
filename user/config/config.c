//
// Created by fxf on 23-9-3.
//

#define LOG_TAG "config.main"

#include <elog.h>
#include <stdio.h>
#include <cJSON.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parameters/pid_ctl.h"
#include "parameters/propeller.h"
#include "parameters/dev_ctl.h"

#include "config.h"

#define CONFIG_FILE_PATH "config.json"
#define CONFIG_FILE_LEN 2048

static void rov_info_write_initial_value(struct rov_info* info)
{
    memset(info, 0, sizeof(rov_info_t));

    propeller_params_init(&info->propeller.front_right);
    propeller_params_init(&info->propeller.front_left);
    propeller_params_init(&info->propeller.center_right);
    propeller_params_init(&info->propeller.center_left);
    propeller_params_init(&info->propeller.back_right);
    propeller_params_init(&info->propeller.back_left);

    pid_ctl_params_init(&info->pidScale.yaw);
    pid_ctl_params_init(&info->pidScale.depth);

    dev_ctl_params_init(&info->devCtl.light);
    dev_ctl_params_init(&info->devCtl.yuntai);
    dev_ctl_params_init(&info->devCtl.arm);
}

static cJSON* dev_ctl_params_write(struct rov_info* info)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "light", dev_ctl_params_add_to_root(&info->devCtl.light));
    cJSON_AddItemToObject(root, "yuntai", dev_ctl_params_add_to_root(&info->devCtl.yuntai));
    cJSON_AddItemToObject(root, "arm", dev_ctl_params_add_to_root(&info->devCtl.arm));

    return root;
}

static cJSON* pid_ctl_params_write(struct rov_info* info)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "yaw_lock", pid_ctl_params_add_to_root(&info->pidScale.yaw));
    cJSON_AddItemToObject(root, "depth_lock", pid_ctl_params_add_to_root(&info->pidScale.depth));

    return root;
}

static cJSON* propeller_params_write(struct rov_info* info)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddNumberToObject(root, "pwm_freq_calibration", info->propeller.pwm_freq_calibration);
    cJSON_AddItemToObject(root, "front_right", propeller_params_add_to_root(&info->propeller.front_right));
    cJSON_AddItemToObject(root, "front_left", propeller_params_add_to_root(&info->propeller.front_left));
    cJSON_AddItemToObject(root, "center_right", propeller_params_add_to_root(&info->propeller.center_right));
    cJSON_AddItemToObject(root, "center_left", propeller_params_add_to_root(&info->propeller.center_left));
    cJSON_AddItemToObject(root, "back_right", propeller_params_add_to_root(&info->propeller.back_right));
    cJSON_AddItemToObject(root, "back_left", propeller_params_add_to_root(&info->propeller.back_left));

    return root;
}

int rov_config_write_to_file(struct rov_info* info)
{
    cJSON* params = cJSON_CreateObject();

    cJSON_AddItemToObject(params, "propeller_params", propeller_params_write(info));
    cJSON_AddItemToObject(params, "pid_clt_params", pid_ctl_params_write(info));
    cJSON_AddItemToObject(params, "dev_ctl_params", dev_ctl_params_write(info));

    char *temp = cJSON_Print(params);
    FILE *fp = fopen(CONFIG_FILE_PATH, "w");
    if (fp == NULL)
    {
        //使用“写入”方式创建文件
        fp = fopen(CONFIG_FILE_PATH, "wt+");
    }
    if (fputs(temp, fp) < 0)   //写入文件
    {
        log_e("error in fputs config file");
        return -1;
    }

    fclose(fp);
    free(temp);
    cJSON_Delete(params);
    return 0;
}

static void propeller_params_read(struct rov_info* info, cJSON *node)
{
    if (node == NULL)
        return;
    info->propeller.pwm_freq_calibration = cJSON_GetObjectItem(node, "pwm_freq_calibration")->valuedouble;
    propeller_params_read_from_root(&info->propeller.front_right, cJSON_GetObjectItem(node, "front_right"));
    propeller_params_read_from_root(&info->propeller.front_left, cJSON_GetObjectItem(node, "front_left"));
    propeller_params_read_from_root(&info->propeller.center_right, cJSON_GetObjectItem(node, "center_right"));
    propeller_params_read_from_root(&info->propeller.center_left, cJSON_GetObjectItem(node, "center_left"));
    propeller_params_read_from_root(&info->propeller.back_right, cJSON_GetObjectItem(node, "back_right"));
    propeller_params_read_from_root(&info->propeller.back_left, cJSON_GetObjectItem(node, "back_left"));
}

static void pid_ctl_params_read(struct rov_info* info, cJSON *node)
{
    if (node == NULL)
        return;
    pid_ctl_params_read_from_root(&info->pidScale.yaw, cJSON_GetObjectItem(node, "yaw_lock"));
    pid_ctl_params_read_from_root(&info->pidScale.depth, cJSON_GetObjectItem(node, "depth_lock"));
}

static void dev_ctl_params_read(struct rov_info* info, cJSON *node)
{
    if (node == NULL)
        return;
    dev_ctl_params_read_from_root(&info->devCtl.arm, cJSON_GetObjectItem(node, "arm"));
    dev_ctl_params_read_from_root(&info->devCtl.light, cJSON_GetObjectItem(node, "light"));
    dev_ctl_params_read_from_root(&info->devCtl.yuntai, cJSON_GetObjectItem(node, "yuntai"));
}

int rov_config_read_from_file(struct rov_info* info)
{
    FILE *fp = fopen(CONFIG_FILE_PATH, "r");
    if (fp == NULL)
    {
        log_e("file no exist");
        return -1;
    }
    char buf[CONFIG_FILE_LEN] = {0};
    log_i("read %d bytes of config file", fread(buf, 1, CONFIG_FILE_LEN, fp));
    cJSON *params = cJSON_Parse(buf);
    if (params != NULL) // propeller_parameters 非空，解析
    {
        propeller_params_read(info, cJSON_GetObjectItem(params, "propeller_params"));
        pid_ctl_params_read(info, cJSON_GetObjectItem(params, "pid_clt_params"));
        dev_ctl_params_read(info, cJSON_GetObjectItem(params, "dev_params"));
    }
    else
    {
        log_e("config file parse error");
        return -1;
    }

    cJSON_Delete(params);
    return 0;
}

int rov_config_init(struct rov_info* info)
{
    log_i("load to config file");
    if (0 == access(CONFIG_FILE_PATH, F_OK)) // 0:存在
    {
        if (rov_config_read_from_file(info) < 0)
        {
            log_e("cannot read config file");
            return -1;
        }
    }
    else
    {
        log_w("config file not exist, create it");
        rov_info_write_initial_value(info);
        if (rov_config_write_to_file(info) < 0)
        {
            log_e("cannot write config file");
            return -1;
        }
    }
    return 0;
}
