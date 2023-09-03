#define LOG_TAG "server.main"

#include <elog.h>
#include <pthread.h>
#include <jsonrpc-c.h>
#include <sys/time.h>

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
    jrpc_register_procedure(&server, move_asyn_handler, "move_asyn", info);
    jrpc_register_procedure(&server, move_syn_handler, "move", info);
    jrpc_register_procedure(&server, move_absolute_handler, "move_absolute", info);
    jrpc_register_procedure(&server, move_relative_handler, "move_relative", info);
    jrpc_register_procedure(&server, catcher_handler, "catch", &info->devCtl);
    jrpc_register_procedure(&server, depth_handler, "depth", &info->devCtl);
    jrpc_register_procedure(&server, direction_lock_handler, "set_direction_locked", &info->devCtl);
    jrpc_register_procedure(&server, depth_lock_handler, "set_depth_locked", &info->devCtl);
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

static struct rov_info* _info_in_rpc = NULL;
void check_lose_status(int signo)
{
    if (_info_in_rpc == NULL)
    {
        return;
    }

    if (_info_in_rpc->devCtl.lose_clt_flag == 0)
    {
        _info_in_rpc->devCtl.lose_clt_flag = 1;
    } else
    {
        _info_in_rpc->rocket.x = 0;
        _info_in_rpc->rocket.y = 0;
        _info_in_rpc->rocket.z = 0;
        _info_in_rpc->rocket.yaw = 0;
    }
}

/**
 * @brief 启动 jsonrpc 服务
 * @param info 含有rov信息的结构体
 * @param port http 服务的端口
 * @return 成功返回 0，失败返回 -1
 */
int jsonrpc_server_run(struct rov_info* info, int port, int clt_timeout_value)
{
    if (jrpc_server_init(&server, port) != 0) {
        log_e("init failed");
        return -1;
    }
    log_i("starting thread");
    if (pthread_create(&info->threadTid.rpc_server, NULL, server_thread, info) != 0)
    {
        log_e("thread start failed");
        return -1;
    }
    pthread_detach(info->threadTid.rpc_server);

    _info_in_rpc = info;
    signal(SIGALRM, check_lose_status);

    struct itimerval tick = {0};
    //Timeout to run first time
    tick.it_value.tv_sec = 30;
    tick.it_value.tv_usec = 0;

    //After first, the Interval time for clock
    tick.it_interval.tv_sec = clt_timeout_value;
    tick.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_REAL, &tick, NULL) < 0)
    {
        log_e("failed to start lose status check");
        return -1;
    }

    return 0;
}

/**
 * @brief jsonrpc 服务
 * @return 成功返回 0，失败返回 -1
 */
int jsonrpc_server_stop()
{
    log_i("stop service");
    struct itimerval tick = {0};
    //Timeout to run first time
    tick.it_value.tv_sec = 0;
    tick.it_value.tv_usec = 0;

    //After first, the Interval time for clock
    tick.it_interval.tv_sec = 0;
    tick.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_REAL, &tick, NULL) < 0)
    {
        log_e("failed to stop lose status check");
    }

    return jrpc_server_stop(&server);
}
