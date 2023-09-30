#ifndef DATA_DEFINE_CONTROL_H
#define DATA_DEFINE_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

struct pwmDev_parameters
{
    int channel;
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

typedef struct debug_info
{
    float auv_expect_depth;
    float depth_diffen;
    float yaw_diffen;
    int propeller_direct_front_left;
    int propeller_direct_front_right;
    int propeller_direct_center_left;
    int propeller_direct_center_right;
    int propeller_direct_back_left;
    int propeller_direct_back_right;
} debug_info_t;

typedef struct thread_tid
{
    unsigned long rpc_server;
    unsigned long device;
    unsigned long control;
} thread_tid_t;

#endif
