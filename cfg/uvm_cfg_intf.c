#include "uvm_cfg_intf.h"

#include "log.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void* uvm_intf_read_from_file() {
    FILE* file;
    long file_size;
    char* buffer;

    // 打开文件
    file = fopen(CONFIG_FILE_PATH, "r");
    if (file == NULL) {
        log_error("Unable to open config file.");
        return NULL;
    }

    // 定位文件末尾以获取文件大小
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // 分配内存来存储文件内容
    buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        log_error("Failed to alloc memory.");
        fclose(file);
        return NULL;
    }

    // 读取文件内容到缓冲区
    int bytes_read = fread(buffer, file_size, 1, file);
    if (bytes_read != 1) {
        log_error("Failed read from file.");
        fclose(file);
        free(buffer);
        return NULL;
    }
    log_info("Successfully read %ld bytes.", file_size);

    // 在缓冲区末尾添加字符串结束符
    buffer[file_size] = '\0';

    // 关闭文件
    fclose(file);

    return buffer;
}

int uvm_intf_write_to_file(const void* content) {
    FILE* file;

    // 打开文件以进行写入
    file = fopen(CONFIG_FILE_PATH, "w");
    if (file == NULL)
    {
        file = fopen(CONFIG_FILE_PATH, "wt+");
        if (file == NULL)
        {
            log_error("Unable to open config file.");
            return -1;
        }
    }

    // 写入内容到文件
    if (fprintf(file, "%s", (const char *)content) < 0) {
        log_error("Write to file failed.");
    }

    // 关闭文件
    fclose(file);
    return 0;
}
