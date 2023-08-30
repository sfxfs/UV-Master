#define LOG_TAG "control.main"

#include <elog.h>
#include <pthread.h>
#include <unistd.h>
#include "pid.h"

#include "control.h"

void *control_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;
    for (;;)
    {

    }
    return NULL;
}

int rov_control_run(struct rov_info* info)
{
    log_i("starting thread");
    if (pthread_create(&info->threadTid.control, NULL, control_thread, info) != 0)
    {
        log_e("thread start failed");
        return -1;
    }
    pthread_detach(info->threadTid.control);
    return 0;
}

int rov_control_stop(struct rov_info* info)
{
    if (pthread_cancel(info->threadTid.control) != 0)
    {
        return -1;
    }
    return 0;
}
