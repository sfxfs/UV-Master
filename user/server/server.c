#define LOG_TAG "server.main"

#include <elog.h>
#include <pthread.h>
#include <sys/time.h>
#include <jsonrpc-c.h>
#include <mln_event.h>

#include "handler/control.h"
#include "handler/debug.h"
#include "handler/info.h"
#include "server.h"

static struct jrpc_server server = {0};
static mln_event_t *ev = NULL;

/**
 * @brief 注册信息相关的回调函数
 * @param info 含有rov信息的结构体
 */
static void info_handler_reg(struct rov_info* info)
{
    jrpc_register_procedure(&server, info_handler, "get_info", &info->sensor);
    jrpc_register_procedure(&server, debug_info_handler, "get_feedbacks", &info->debugInfo);
    jrpc_register_procedure(&server, update_handler, "update_firmware", NULL);
}

/**
 * @brief 注册控制相关的回调函数
 * @param info 含有rov信息的结构体
 */
static void control_handler_reg(struct rov_info* info)
{
    jrpc_register_procedure(&server, move_asyn_handler, "move_asyn", info);
    jrpc_register_procedure(&server, move_syn_handler, "move", info);
    jrpc_register_procedure(&server, move_absolute_handler, "move_absolute", info);
    jrpc_register_procedure(&server, move_relative_handler, "move_relative", info);
    jrpc_register_procedure(&server, catcher_handler, "catch", &info->devCtl);
    jrpc_register_procedure(&server, light_handler, "light", &info->devCtl);
    jrpc_register_procedure(&server, depth_handler, "depth", &info->debugInfo);
    jrpc_register_procedure(&server, direction_lock_handler, "set_direction_locked", &info->devCtl);
    jrpc_register_procedure(&server, depth_lock_handler, "set_depth_locked", &info->devCtl);
}

/**
 * @brief 注册调试相关的回调函数
 * @param info 含有rov信息的结构体
 */
static void debug_handler_reg(struct rov_info* info)
{
    jrpc_register_procedure(&server, set_debug_mode_enabled_handler, "set_debug_mode_enabled", &info->devCtl);
    jrpc_register_procedure(&server, set_propeller_pwm_freq_calibration_handler, "set_propeller_pwm_freq_calibration", info);
    jrpc_register_procedure(&server, set_propeller_values_handler, "set_propeller_values", info);
    jrpc_register_procedure(&server, load_handler, "load_parameters", info);
    jrpc_register_procedure(&server, save_handler, "save_parameters", info);
}

/**
 * @brief jsonrpc 线程
 * @param arg 线程传参
 * @return 线程返回值
 */
void *server_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;

    info_handler_reg(info);
    control_handler_reg(info);
    debug_handler_reg(info);

    jrpc_server_run(&server);
    //running...
    jrpc_server_destroy(&server);
    return NULL;
}

void *check_lose_thread(void *arg)
{
    for (;;)
        mln_event_dispatch(ev);
    return NULL;
}

/**
 * @brief 检查失联状态
 * @param ev mln_event_t 事件模块
 * @param data rov_info_t 结构体参数
 */
static void check_lose_status(mln_event_t *ev, void *data)
{
    rov_info_t *info = (rov_info_t *)data;
    if (info == NULL)
    {
        return;
    }

    if (info->devCtl.lose_clt_flag == 0)
    {
        info->devCtl.lose_clt_flag = 1;
    } else
    {
        info->rocket.x = 0;
        info->rocket.y = 0;
        info->rocket.z = 0;
        info->rocket.yaw = 0;
    }
    if (info->server.clt_timeout)
        mln_event_timer_set(ev, info->server.clt_timeout, data, check_lose_status);
}

/**
 * @brief 启动 jsonrpc 服务
 * @param info 含有rov信息的结构体
 * @param port http 服务的端口
 * @return 成功返回 0，失败返回 -1
 */
int jsonrpc_server_run(struct rov_info* info)
{
    if (jrpc_server_init(&server, info->server.port) != 0) {
        log_e("init failed");
        return -1;
    }
    log_i("starting thread");
    if (pthread_create(&info->thread.tid.rpc_server, NULL, server_thread, info) != 0)
    {
        log_e("thread start failed");
        return -1;
    }
    pthread_detach(info->thread.tid.rpc_server);

    if (info->server.clt_timeout)
    {
        ev = mln_event_new();
        if (ev == NULL)
        {
            log_e("event init failed");
            return -1;
        }

        if (mln_event_timer_set(ev, info->server.clt_timeout, info, check_lose_status) < 0)
        {
            log_e("timer set failed");
            return -1;
        }

        if (pthread_create(&info->thread.tid.loss_status_check, NULL, check_lose_thread, NULL) != 0)
        {
            log_e("loss check thread start failed");
            return -1;
        }
        pthread_detach(info->thread.tid.loss_status_check);
    }

    return 0;
}

/**
 * @brief 停止 jsonrpc 服务
 * @return 成功返回 0，失败返回 -1
 */
int jsonrpc_server_stop()
{
    log_i("stop service");

    mln_event_free(ev);//释放事件模块

    return jrpc_server_stop(&server);
}
