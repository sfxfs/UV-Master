#define LOG_TAG "server.main"

#include <elog.h>
#include <pthread.h>

#include "../../protocols/jsonrpc-c.h"
#include "handler.h"
#include "server.h"

static struct jrpc_server server = {0};

/**
 * @brief 注册信息相关的回调函数
 * @param info 含有rov信息的结构体
 */
static void info_handler_reg(struct rov_info* info)
{
    jrpc_register_procedure(&server, info_handler, "get_info", &info->sensor);
    jrpc_register_procedure(&server, debug_info_handler, "get_feedbacks", NULL);
    jrpc_register_procedure(&server, update_handler, "update_firmware", NULL);
}

/**
 * @brief 注册控制相关的回调函数
 * @param info 含有rov信息的结构体
 */
static void control_handler_reg(struct rov_info* info)
{
    jrpc_register_procedure(&server, move_asyn_handler, "move_asyn", &info->rocket);
    jrpc_register_procedure(&server, move_syn_handler, "move", &info->rocket);
    jrpc_register_procedure(&server, move_absolute_handler, "move_absolute", &info->rocket);
    jrpc_register_procedure(&server, move_relative_handler, "move_relative", &info->rocket);
    jrpc_register_procedure(&server, catcher_handler, "catch", NULL);
    jrpc_register_procedure(&server, depth_handler, "depth", NULL);
    jrpc_register_procedure(&server, direction_lock_handler, "set_direction_locked", NULL);
    jrpc_register_procedure(&server, depth_lock_handler, "set_depth_locked", NULL);
}

/**
 * @brief 注册调试相关的回调函数
 * @param info 含有rov信息的结构体
 */
static void debug_handler_reg(struct rov_info* info)
{
    jrpc_register_procedure(&server, set_debug_mode_enabled_handler, "set_debug_mode_enabled", NULL);
    jrpc_register_procedure(&server, set_propeller_pwm_freq_calibration_handler, "set_propeller_pwm_freq_calibration", NULL);
    jrpc_register_procedure(&server, set_propeller_values_handler, "set_propeller_values", NULL);
    jrpc_register_procedure(&server, set_propeller_parameters_handler, "set_propeller_parameters", NULL);
    jrpc_register_procedure(&server, set_control_loop_parameters_handler, "set_control_loop_parameters", NULL);
    jrpc_register_procedure(&server, load_handler, "load_parameters", NULL);
    jrpc_register_procedure(&server, save_handler, "save_parameters", NULL);
}

/**
 * @brief jsonrpc 线程
 * @param arg
 * @return
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
    return 0;
}

/**
 * @brief 启动 jsonrpc 服务
 * @param info 含有rov信息的结构体
 * @param port http 服务的端口
 * @return 成功返回 0，失败返回 -1
 */
int jsonrpc_server_run(struct rov_info* info, int port)
{
    if (jrpc_server_init(&server, port) != 0) {
        log_e("init failed");
        return -1;
    }
    log_i("starting thread");
    pthread_t server_tid;
    if (pthread_create(&server_tid, NULL, server_thread, info) != 0)
    {
        log_e("thread start failed");
        return -1;
    }
    pthread_detach(server_tid);
    return 0;
}

/**
 * @brief jsonrpc 服务
 * @return 成功返回 0，失败返回 -1
 */
int jsonrpc_server_stop()
{
    log_i("stop service");
    return jrpc_server_stop(&server);
}
