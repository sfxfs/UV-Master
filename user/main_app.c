//
// Created by fxf on 23-9-2.
//

#define LOG_TAG "uvm.main"

#include <elog.h>
#include <stdlib.h>
#include <unistd.h>
#include "server/server.h"
#include "device/device.h"
#include "config/config.h"
#include "control/control.h"

rov_info_t uvmInfo;

/**
 * @brief 停止uvm服务
 */
void uvm_deinit()
{
    jsonrpc_server_stop();
    rov_device_stop(&uvmInfo);
}

/**
 * @brief uvm初始化
 * @param debug_mode 调试模式
 */
void uvm_init(bool debug_mode)
{
    if (debug_mode == true)
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

    if (rov_config_init(&uvmInfo) < 0)
        exit(-1);

    if (jsonrpc_server_run(&uvmInfo) < 0)
        exit(-1);

    if (rov_device_run(&uvmInfo) < 0)
    {
        jsonrpc_server_stop();
        exit(-1);
    }

    if (rov_control_run(&uvmInfo) < 0)
    {
        uvm_deinit();
        exit(-1);
    }
}

void uvm_loop()
{
    sleep(1);
}
