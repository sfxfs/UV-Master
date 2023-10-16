#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include "data_define.h"
#include "jy901.h"

int motion_sensor_init (rov_info_t *info);
void motion_sensor_run (void);

#endif
