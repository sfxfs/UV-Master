#define LOG_TAG "rov.main"

#include <unistd.h>
#include "../log-sys/elog.h"
#include "server/server.h"
#include "control/control.h"
#include "device/device.h"

rov_info_t rovInfo = {0};

int main(int argc, char **argv)
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

    jsonrpc_server_run(&rovInfo, 8888);

    for (;;)
    {
        log_i("rocket.x:%lf\n", rovInfo.rocket.x);
        log_i("rocket.y:%lf\n", rovInfo.rocket.y);
        log_i("rocket.z:%lf\n", rovInfo.rocket.z);
        log_i("rocket.yaw:%lf\n", rovInfo.rocket.yaw);
        sleep(1);
    }

    return 0;
}
