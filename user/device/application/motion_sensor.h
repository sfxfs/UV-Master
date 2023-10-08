#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include "data_define.h"
#include "jy901.h"

int motion_sensor_init (void);
int motion_sensor_uart_data_in (uint8_t byte);
int motion_sensor_get_data (sensor_t *data);

#endif
