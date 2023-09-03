//
// Created by fxf on 23-9-2.
//

#define LOG_TAG "rov.main"

#include <elog.h>
#include <stdlib.h>
#include <unistd.h>
#include "server/server.h"
#include "device/device.h"

rov_info_t rovInfo = {0};

void deinit()
{
    rov_device_stop(&rovInfo);
    jsonrpc_server_stop();
}

void init(int debug_mode)
{
    if (debug_mode)
    {
        // 初始化 EasyLogger
        elog_init();
        /* 设置 EasyLogger 日志格式 */
        elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
        elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
        elog_set_text_color_enabled(true);
        elog_start();
    }

    if (jsonrpc_server_run(&rovInfo, 8888, 3) < 0)
    {
        deinit();
        exit(-1);
    }
    rov_device_run(&rovInfo);
}

void loop()
{
    sleep(1);
}
