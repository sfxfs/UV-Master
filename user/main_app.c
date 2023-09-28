//
// Created by fxf on 23-9-2.
//

#define LOG_TAG "rov.main"

#include <elog.h>
#include <stdlib.h>
#include <unistd.h>
#include "server/server.h"
#include "device/device.h"
#include "config/config.h"
#include "control/control.h"

rov_info_t rovInfo = {0};

void rov_deinit()
{
    jsonrpc_server_stop();
}

void rov_init(int debug_mode)
{
    if (debug_mode)
    {
        // 初始化 EasyLogger
        elog_init();
        /* 设置 EasyLogger 日志格式 */
        elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
        elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_TIME | ELOG_FMT_LVL | ELOG_FMT_TAG);
        elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_TIME | ELOG_FMT_LVL | ELOG_FMT_TAG);
        elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_TIME | ELOG_FMT_LVL | ELOG_FMT_TAG);
        elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
        elog_set_text_color_enabled(true);
        elog_start();
    }

    if (rov_config_init(&rovInfo) < 0)
    {
        rov_deinit();
        exit(-1);
    }

    if (jsonrpc_server_run(&rovInfo, 8888, 3) < 0)
    {
        rov_deinit();
        exit(-1);
    }
}

void rov_loop()
{
    sleep(1);
}
