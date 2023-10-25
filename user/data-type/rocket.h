#ifndef DATA_DEFINE_ROCKET_H
#define DATA_DEFINE_ROCKET_H

#include <stdint.h>
#include <stdbool.h>

typedef struct rocket_button_attr
{
    bool triggered;
    int value;
} rocket_button_attr_t;

typedef struct rocket_propeller_attr
{
    float ratio_p;
    float ratio_n;
    bool reversed;
} rocket_propeller_attr_t;

typedef struct rocket_axis_attr
{
    float value;
    struct rocket_propeller_attr front_left;
    struct rocket_propeller_attr front_right;
    struct rocket_propeller_attr center_left;
    struct rocket_propeller_attr center_right;
    struct rocket_propeller_attr back_left;
    struct rocket_propeller_attr back_right;
} rocket_axis_attr_t;

typedef struct rocket
{
    struct rocket_axis_attr L_UD;   // 左摇杆 上下轴
    struct rocket_axis_attr L_LR;   // 左摇杆 左右轴
    struct rocket_axis_attr R_UD;   // 右摇杆 上下轴
    struct rocket_axis_attr R_LR;   // 右摇杆 左右轴
} rocket_t;

#endif
