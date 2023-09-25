#ifndef DATA_DEFINE_DEVICE_H
#define DATA_DEFINE_DEVICE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct sensor
{
    float depth;
    float pitch;
    float roll;
    float yaw;
    float temperature;
} sensor_t;

#endif
