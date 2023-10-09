#ifndef DATA_DEFINE_PROPELLER_H
#define DATA_DEFINE_PROPELLER_H

#include <stdint.h>
#include <stdbool.h>

struct propeller_parameters
{
    uint8_t enabled : 1;
    uint8_t reversed : 1;
    int channel;
    int deadzone_upper;  // 0 ~ 1000
    int deadzone_lower;  // -0 ~ -1000
    double power_negative;
    double power_positive;
    double power_cur;   // -1.0 ~ 1.0
    double power_last;
};

typedef struct propeller
{
    uint16_t pwm_freq_calibration;
    struct propeller_parameters front_left;
    struct propeller_parameters front_right;
    struct propeller_parameters center_left;
    struct propeller_parameters center_right;
    struct propeller_parameters back_left;
    struct propeller_parameters back_right;
} propeller_t;

#endif
