#ifndef DATA_DEFINE_PROPELLER_H
#define DATA_DEFINE_PROPELLER_H

#include <stdint.h>
#include <stdbool.h>

struct propeller_parameters
{
    uint8_t enabled : 1;
    uint8_t reversed : 1;
    int channel;
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

#endif
