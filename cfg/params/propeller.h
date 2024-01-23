#ifndef UVM_CFG_PROPELLER_H
#define UVM_CFG_PROPELLER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    bool reversed;
    bool enabled;
    int16_t channel;
    int16_t deadzone_upper; // us
    int16_t deadzone_lower;
    float power_positive; // -1.0 ~ 1.0
    float power_negative;
} propeller_attr;

typedef struct
{
    int16_t pwm_freq_offset;
    propeller_attr front_right_attr;
    propeller_attr front_left_attr;
    propeller_attr center_right_attr;
    propeller_attr center_left_attr;
    propeller_attr back_right_attr;
    propeller_attr back_left_attr;
} propeller_params;

propeller_params *propeller_create_with_init_val (void);
void *propeller_s2j (propeller_params *params);
propeller_params *propeller_j2s (void *json);

#endif
