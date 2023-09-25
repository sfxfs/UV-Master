#ifndef DATA_DEFINE_PID_H
#define DATA_DEFINE_PID_H

#include <stdint.h>
#include <stdbool.h>

struct pid_scale_parameters
{
    float Kp;
    float Ki;
    float Kd;
};

typedef struct pid_scale
{
    struct pid_scale_parameters yaw;
    struct pid_scale_parameters depth;
} pid_scale_t;

#endif
