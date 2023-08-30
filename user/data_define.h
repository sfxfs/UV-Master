//
// Created by fxf on 23-7-9.
//

#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H

#include <stdint.h>

struct propeller_parameters
{
    uint8_t enabled : 1;
    uint8_t reversed : 1;
    float deadzone_upper;
    float deadzone_lower;
    double power_negative;
    double power_positive;
    float power_cur;
    float power_last;
};

typedef struct propeller
{
    struct propeller_parameters front_left;
    struct propeller_parameters front_right;
    struct propeller_parameters center_left;
    struct propeller_parameters center_right;
    struct propeller_parameters back_left;
    struct propeller_parameters back_right;
} propeller_t;

typedef struct thread_tid
{
    unsigned long rpc_server;
    unsigned long device;
    unsigned long control;
} thread_tid_t;

typedef struct dev_fd
{
    int depth_sensor_fd;
    int motion_sensor_fd;
    int pwm_controller_fd;
} dev_fd_t;

typedef struct dev_ctl
{
    int depth_lock;
    int dir_lock;
    int catcher_clt;
    int light_clt;
    int debug_mode_stat;
} dev_ctl_t;

typedef struct sensor
{
    float depth;
    float pitch;
    float roll;
    float yaw;
    float temperature;
} sensor_t;

typedef struct rocket
{
    double x;  //左右
    double y;  //前后
    double z;  //上下
    double yaw;//旋转
} rocket_t;

typedef struct rov_info {
    struct rocket rocket;
    struct propeller propeller;
    struct sensor sensor;
    struct dev_ctl devCtl;
    struct dev_fd devFd;
    struct thread_tid threadTid;
} rov_info_t;

#endif //DATA_DEFINE_H
