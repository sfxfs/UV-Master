#define LOG_TAG "server.main"

#include "server.h"

#include <elog.h>
#include <pthread.h>
#include <sys/time.h>
#include <mln_event.h>
#include <onion/log.h>
#include <onion/block.h>
#include <onion/onion.h>
#include "handler/info.h"
#include "handler/debug.h"
#include "handler/control.h"

static rpc_handle_t rpc;
static mln_event_t *ev;
static onion *o;
static onion_url *url;

/**
 * @brief 注册信息相关的回调函数
 * @param info 含有rov信息的结构体
 */
static void info_handler_reg(struct rov_info* info)
{
    rpc_add_method(&rpc, info_handler, "get_info", &info->device.sensor);
    rpc_add_method(&rpc, debug_info_handler, "get_feedbacks", NULL);
    rpc_add_method(&rpc, update_handler, "update_firmware", NULL);
}

/**
 * @brief 注册控制相关的回调函数
 * @param info 含有rov信息的结构体
 */
static void control_handler_reg(struct rov_info* info)
{
    rpc_add_method(&rpc, move_syn_handler, "move", info);
    rpc_add_method(&rpc, move_absolute_handler, "move_absolute", info);
    rpc_add_method(&rpc, move_relative_handler, "move_relative", info);
    rpc_add_method(&rpc, catcher_handler, "catch", NULL);
    rpc_add_method(&rpc, light_handler, "light", NULL);
    rpc_add_method(&rpc, depth_handler, "depth", NULL);
    rpc_add_method(&rpc, direction_lock_handler, "set_direction_locked", NULL);
    rpc_add_method(&rpc, depth_lock_handler, "set_depth_locked", NULL);
}

/**
 * @brief 注册调试相关的回调函数
 * @param info 含有rov信息的结构体
 */
static void debug_handler_reg(struct rov_info* info)
{
    rpc_add_method(&rpc, set_debug_mode_enabled_handler, "set_debug_mode_enabled", NULL);
    rpc_add_method(&rpc, set_propeller_pwm_freq_calibration_handler, "set_propeller_pwm_freq_calibration", info);
    rpc_add_method(&rpc, set_propeller_values_handler, "set_propeller_values", info);
    rpc_add_method(&rpc, load_handler, "load_parameters", NULL);
    rpc_add_method(&rpc, save_handler, "save_parameters", info);
}

void *check_lose_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;
    while (info->system.server.config.clt_timeout)
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
    if (data == NULL)
    {
        return;
    }
    rov_info_t *info = (rov_info_t *)data;

    pthread_mutex_lock(&info->system.server.loss_status_mtx);
    if (info->control.flag.lose_clt == false)
    {
        info->control.flag.lose_clt = true;
    } else
    {
        info->rocket.L_LR.value = 0;
        info->rocket.L_UD.value = 0;
        info->rocket.R_LR.value = 0;
        info->rocket.R_UD.value = 0;
    }
    pthread_mutex_unlock(&info->system.server.loss_status_mtx);

    if (info->system.server.config.clt_timeout)
        mln_event_timer_set(ev, info->system.server.config.clt_timeout, info, check_lose_status);
}

onion_connection_status strip_rpc(void *data, onion_request * req, onion_response * res)
{
    const onion_block *dreq = onion_request_get_data(req);
    char *ret = rpc_process(&rpc, onion_block_data(dreq), onion_block_size(dreq));
    onion_response_write(res, ret, strlen(ret));
    free(ret);

    rov_info_t *info = (rov_info_t *)data;
    if (info->system.server.config.clt_timeout)
    {
        pthread_mutex_lock(&info->system.server.loss_status_mtx);
        info->control.flag.lose_clt = 0;
        pthread_mutex_unlock(&info->system.server.loss_status_mtx);
    }
    return OCS_PROCESSED;
}

int loss_ctl_timer_init(struct rov_info* info)
{
    pthread_mutex_init(&info->system.server.loss_status_mtx, NULL);

    ev = mln_event_new();
    if (ev == NULL)
    {
        log_w("event init failed");
        return -1;
    }

    if (mln_event_timer_set(ev, info->system.server.config.clt_timeout, info, check_lose_status) < 0)
    {
        log_w("timer set failed");
        return -1;
    }

    if (pthread_create(&info->system.server.loss_status_check_tid, NULL, check_lose_thread, info) != 0)
    {
        log_w("loss check thread start failed");
        return -1;
    }
    pthread_detach(info->system.server.loss_status_check_tid);
    return 0;
}

/**
 * @brief 启动 jsonrpc 服务
 * @param info 含有rov信息的结构体
 * @param port http 服务的端口
 * @return 成功返回 0，失败返回 -1
 */
int jsonrpc_server_run(struct rov_info* info, uint8_t debug_level)
{
    o = onion_new(O_DETACH_LISTEN | O_NO_SIGTERM);
    if (o == NULL)
    {
        log_e("http server init failed");
        return -1;
    }
    if (info->system.server.config.port)
        onion_set_port(o, info->system.server.config.port);
    else
        log_w("port of http server not set, use \"8080\"");
    url = onion_root_url(o);
    if (url == NULL)
    {
        log_e("onion set url failed");
        return -1;
    }
    onion_url_add_with_data(url, "", strip_rpc, info, NULL);

    // 设置 onion 的日志等级
    if (debug_level <= ELOG_LVL_INFO)
    {
        extern int onion_log_flags;
        onion_log_flags = OF_INIT | OF_NOINFO;
    }
    // 设置 jsonrpc 的日志等级
    if (debug_level == ELOG_LVL_INFO)
        rpc.debug_level = 1;
    if (debug_level == ELOG_LVL_DEBUG)
        rpc.debug_level = 2;

    info_handler_reg(info);
    control_handler_reg(info);
    debug_handler_reg(info);

    log_i("starting thread");
    if (onion_listen(o) != 0)
    {
        log_e("thread start failed");
        return -1;
    }

    if (info->system.server.config.clt_timeout)
        if (loss_ctl_timer_init(info) != 0)
            log_w("loss ctl init failed");

    return 0;
}

/**
 * @brief 停止 jsonrpc 服务
 * @return 成功返回 0，失败返回 -1
 */
int jsonrpc_server_stop()
{
    log_i("stop service");

    if (ev != NULL)
        mln_event_free(ev);//释放事件模块
    onion_free(o);

    return 0;
}
