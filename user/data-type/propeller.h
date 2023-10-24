#ifndef DATA_DEFINE_PROPELLER_H
#define DATA_DEFINE_PROPELLER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct propeller_attr
{
    float power_cur;    // -1.0 ~ 1.0
    float power_last;   // -1.0 ~ 1.0
    int power_debug;    // -500 ~ 500 us

    bool enabled;
    bool reversed;
    int channel;
    int deadzone_upper;  // 0 ~ 500 us
    int deadzone_lower;  // 0 ~ -500 us
    float power_negative;
    float power_positive;
} propeller_attr_t;

typedef struct propeller
{
    uint16_t pwm_freq_calibration;
    struct propeller_attr front_left;
    struct propeller_attr front_right;
    struct propeller_attr center_left;
    struct propeller_attr center_right;
    struct propeller_attr back_left;
    struct propeller_attr back_right;
} propeller_t;

#endif
