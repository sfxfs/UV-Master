#ifndef DATA_DEFINE_ROCKET_H
#define DATA_DEFINE_ROCKET_H

#include <stdint.h>
#include <stdbool.h>

struct power_dir
{
    uint8_t reversed;
    double p;
    double n;
};

struct r2p_ratio
{
    struct power_dir front_left;
    struct power_dir front_right;
    struct power_dir center_left;
    struct power_dir center_right;
    struct power_dir back_left;
    struct power_dir back_right;
};

typedef struct rocket
{
    double x;  //左右
    double y;  //前后
    double z;  //上下
    double yaw;//旋转
    struct r2p_ratio ratio_x;
    struct r2p_ratio ratio_y;
    struct r2p_ratio ratio_z;
    struct r2p_ratio ratio_yaw;
} rocket_t;

#endif
