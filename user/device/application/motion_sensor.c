#define LOG_TAG "device.motion_sensor"

#include <elog.h>
#include "other_utils.h"
#include "motion_sensor.h"
#include "device/interface/jy901_interface.h"

static jy901_handle_t jy901_handle = {0};

int motion_sensor_init ()
{
    jy901_handle.SerialInit = jy901_interface_uart_init;
    jy901_handle.SerialWrite = jy901_interface_uart_write;
    jy901_handle.DelaymsCb = rov_delay;
    if (WitInit(&jy901_handle) != WIT_HAL_OK)
    {
        log_e("uart init failed");
        return -1;
    }
    return 0;
}

int motion_sensor_uart_data_in (uint8_t byte)
{
    WitSerialDataIn(&jy901_handle, byte);
    return 0;
}

int motion_sensor_get_data (sensor_t *data)
{
    data->yaw = jy901_handle.fAngle[2];     //z
    data->pitch = jy901_handle.fAngle[1];   //y
    data->roll = jy901_handle.fAngle[0];    //x
    return 0;
}
