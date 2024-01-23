#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "cjson/cJSON.h"

#include "uvm-cfg.h"

#define CONFIG_FILE_PATH "config.json"

static config_data uvm_cfg_initialize_value()
{
    config_data data_s = {0};

    data_s.dev_ctl = dev_ctl_create_with_init_val();
    data_s.propeller = propeller_create_with_init_val();
    data_s.rocket_ratio = rocket_ratio_create_with_init_val();
    data_s.others = others_create_with_init_val();

    if (data_s.dev_ctl && data_s.propeller && data_s.rocket_ratio && data_s.others)
        data_s.read_succeed = true;
    return data_s;
}

void uvm_cfg_delete(config_data data_s)
{
    if (data_s.dev_ctl)
        free(data_s.dev_ctl);
    if (data_s.propeller)
        free(data_s.propeller);
    if (data_s.rocket_ratio)
        free(data_s.rocket_ratio);
    if (data_s.others)
        free(data_s.others);
}

static char* read_from_file(const char* filename) {
    FILE* file;
    long file_size;
    char* buffer;

    // 打开文件
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("CFG: Unable to open config file.\n");
        return NULL;
    }

    // 定位文件末尾以获取文件大小
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // 分配内存来存储文件内容
    buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("CFG: Failed to alloc memory.\n");
        fclose(file);
        return NULL;
    }

    // 读取文件内容到缓冲区
    int bytes_read = fread(buffer, file_size, 1, file);
    printf("CFG: successfully read %d bytes.\n", bytes_read);
    if (bytes_read != 1) {
        printf("CFG: Failed read from file.\n");
        fclose(file);
        free(buffer);
        return NULL;
    }

    // 在缓冲区末尾添加字符串结束符
    buffer[file_size] = '\0';

    // 关闭文件
    fclose(file);

    return buffer;
}

config_data uvm_cfg_read ()
{
    config_data config = {0};

    char *data = read_from_file(CONFIG_FILE_PATH);
    if (data == NULL)
    {
        return config;
    }
    cJSON *json = cJSON_Parse(data);
    free(data);
    if (json == NULL)
    {
        return config;
    }

    config.others = others_j2s(cJSON_GetObjectItem(json, "others_params"));
    config.dev_ctl = dev_ctl_j2s(cJSON_GetObjectItem(json, "dev_ctl_params"));
    config.propeller = propeller_j2s(cJSON_GetObjectItem(json, "propeller_params"));
    config.rocket_ratio = rocket_ratio_j2s(cJSON_GetObjectItem(json, "rocket_ratio_params"));

    cJSON_Delete(json);

    if (config.dev_ctl && config.propeller && config.rocket_ratio && config.others)
        config.read_succeed = true;
    return config;
}

static int write_to_file(const char* filename, const char* content) {
    FILE* file;

    // 打开文件以进行写入
    file = fopen(filename, "w");
    if (file == NULL)
    {
        file = fopen(CONFIG_FILE_PATH, "wt+");
        if (file == NULL)
        {
            printf("CFG: Unable to open config file.\n");
            return -1;
        }
    }

    // 写入内容到文件
    if (fprintf(file, "%s", content) < 0) {
        printf("CFG: write to file failed.\n");
    }

    // 关闭文件
    fclose(file);
    return 0;
}

int uvm_cfg_write(config_data data_s)
{
    cJSON *json = cJSON_CreateObject();

    cJSON_AddItemToObject(json, "others_params", others_s2j(data_s.others));
    cJSON_AddItemToObject(json, "dev_ctl_params", dev_ctl_s2j(data_s.dev_ctl));
    cJSON_AddItemToObject(json, "propeller_params", propeller_s2j(data_s.propeller));
    cJSON_AddItemToObject(json, "rocket_ratio_params", rocket_ratio_s2j(data_s.rocket_ratio));

    char *str = cJSON_Print(json);
    cJSON_Delete(json);

    int ret = write_to_file(CONFIG_FILE_PATH, str);
    free(str);

    return ret;
}

config_data uvm_cfg_init()
{
    if (0 == access(CONFIG_FILE_PATH, F_OK)) // 0:存在
    {
        return uvm_cfg_read();
    }

    config_data config = uvm_cfg_initialize_value(); // 初始化Rov_info
    if (uvm_cfg_write(config) < 0)    // 创建并将Rov_info信息写至config
    {
        printf("CFG: Config file write error...\n");
    }

    return config;
}
