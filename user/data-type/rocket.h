#ifndef DATA_DEFINE_ROCKET_H
#define DATA_DEFINE_ROCKET_H

#include <stdint.h>
#include <stdbool.h>

struct power_dir
{
    uint8_t reversed;
    float p;
    float n;
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
    float x;  //左右
    float y;  //前后
    float z;  //上下
    float yaw;//旋转
    struct r2p_ratio ratio_x;
    struct r2p_ratio ratio_y;
    struct r2p_ratio ratio_z;
    struct r2p_ratio ratio_yaw;
} rocket_t;

#endif
