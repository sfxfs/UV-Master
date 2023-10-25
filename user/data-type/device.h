#ifndef DATA_DEFINE_DEVICE_H
#define DATA_DEFINE_DEVICE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct pwmDev_attr
{
    bool enabled;
    int cur;
    int channel;
    int pMax;
    int nMax;
    int reset;
    int step;
} pwmDev_attr_t;

typedef struct sensorDev_info
{
    float pitch;
    float roll;
    float yaw;

    float depth;
    float temperature;
} sensorDev_info_t;

typedef struct device
{
    struct pwmDev_attr arm;
    struct pwmDev_attr light;
    struct sensorDev_info sensor;
} device_t;


#endif
