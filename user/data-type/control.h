#ifndef DATA_DEFINE_CONTROL_H
#define DATA_DEFINE_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

struct status_flag
{
    bool lose_clt;
    bool debug_mode;
};

struct pid_scale_attr
{
    float Kp;
    float Ki;
    float Kd;
};

typedef struct pid_scale
{
    struct pid_scale_attr yaw;
    struct pid_scale_attr depth;
} pid_scale_t;

typedef struct control
{
    struct status_flag flag;
    struct pid_scale pid_config;
} control_t;


#endif
