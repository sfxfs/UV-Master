#define LOG_TAG "control.main"

#include "control.h"

#include <elog.h>
#include <unistd.h>
#include <pthread.h>
#include "ctrlPart/depth_ctl.h"
#include "ctrlPart/manual_ctl.h"
#include "ctrlPart/rotate_ctl.h"


/**
 * @brief RPC服务端线程（推进器控制线程）
 * @param arg 输入推进器控制信息，输入类型为void * （rov_info_t *）
 * @return NULL
 */
void *control_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;
    for (;;)
    {
        pthread_mutex_lock(&info->system.control.recv_cmd_mtx);
        pthread_cond_wait(&info->system.control.recv_cmd_cond, &info->system.control.recv_cmd_mtx);
        log_d("cmd recv, ask for propeller");
        if (info->control.flag.debug_mode == false)
        {
            rov_manual_control(info);
        }
        else
        {
            rov_debug_control(info);
        }
        pthread_cond_signal(&info->system.device.power_output_cond);
        pthread_mutex_unlock(&info->system.control.recv_cmd_mtx);
    }
    return NULL;
}

/**
 * @brief 启动推进器控制线程
 * @param info rov_info结构体参数
 * @return 0 ：成功  -1：失败
 */
int rov_control_run(struct rov_info* info)
{
    pthread_mutex_init(&info->system.control.recv_cmd_mtx, NULL);
    pthread_cond_init(&info->system.control.recv_cmd_cond, NULL);

    log_i("starting thread");
    if (pthread_create(&info->system.control.main_tid, NULL, control_thread, info) != 0)
    {
        log_e("thread start failed");
        return -1;
    }
    pthread_detach(info->system.control.main_tid);
    return 0;
}

/**
 * @brief 取消推进器控制线程
 * @param info rov_info结构体参数
 * @return 0:成功 -1：失败
 */
int rov_control_stop(struct rov_info* info)
{
    if (pthread_cancel(info->system.control.main_tid) != 0)
    {
        log_e("cancel thread failed");
        return -1;
    }
    return 0;
}
