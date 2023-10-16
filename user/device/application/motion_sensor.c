#define LOG_TAG "device.motion_sensor"

#include <elog.h>
#include "mln_event.h"
#include "other_utils.h"
#include "motion_sensor.h"
#include "device/interface/jy901_interface.h"

static jy901_handle_t jy901_handle = {0};
static mln_event_t *ev = NULL;

static void motion_sensor_get_data (sensor_t *data)
{
    data->yaw = jy901_handle.fAngle[2];     //z
    data->pitch = jy901_handle.fAngle[1];   //y
    data->roll = jy901_handle.fAngle[0];    //x
}

static void motion_sensor_uart_data_read (mln_event_t *ev, int fd, void *data)
{
    rov_info_t *info = (rov_info_t *)data;
    while (jy901_interface_uart_avail())
        WitSerialDataIn(&jy901_handle, jy901_interface_uart_read());
    motion_sensor_get_data(&info->sensor);
    mln_event_fd_set(ev, fd, M_EV_RECV, M_EV_UNLIMITED, data, motion_sensor_uart_data_read);
}

int motion_sensor_init (rov_info_t *info)
{
    int fd = jy901_interface_uart_init();
    if (fd < 0)
    {
        log_e("uart init failed");
        return -1;
    }
    jy901_handle.SerialWrite = jy901_interface_uart_write;
    jy901_handle.DelaymsCb = uvm_delay;

    ev = mln_event_new();
    if (ev == NULL) {
        log_e("event init failed");
        return -1;
    }

    if (mln_event_fd_set(ev, fd, M_EV_RECV, M_EV_UNLIMITED, info, motion_sensor_uart_data_read) < 0) {
        log_e("fd handler set failed");
        return -1;
    }

    return 0;
}

void motion_sensor_run (void)
{
    mln_event_dispatch(ev);
}
