//
// Created by fxf on 23-7-9.
//

#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H

#include <stdint.h>

struct pid_scale_parameters
{
    float Kp;
    float Ki;
    float Kd;
};

typedef struct pid_scale
{
    float depth_diffen;
    float yaw_diffen;
    struct pid_scale_parameters yaw;
    struct pid_scale_parameters depth;
} pid_scale_t;

struct propeller_parameters
{
    uint8_t enabled : 1;
    uint8_t reversed : 1;
    double deadzone_upper;
    double deadzone_lower;
    double power_negative;
    double power_positive;
    double power_cur;
    double power_last;
};

typedef struct propeller
{
    double pwm_freq_calibration;
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

struct pwmDev_parameters
{
    int pMax;
    int nMax;
    int reset;
    int speed;
};

typedef struct dev_ctl
{
    uint8_t depth_lock : 1;
    uint8_t dir_lock : 1;
    uint8_t catcher_clt : 2;
    uint8_t light_clt : 2;
    uint8_t debug_mode_stat : 1;
    uint8_t lose_clt_flag : 1;
    struct pwmDev_parameters light;
    struct pwmDev_parameters yuntai;
    struct pwmDev_parameters arm;
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
    struct pid_scale pidScale;
    struct sensor sensor;
    struct dev_ctl devCtl;
    struct dev_fd devFd;
    struct thread_tid threadTid;
} rov_info_t;

#endif //DATA_DEFINE_H
