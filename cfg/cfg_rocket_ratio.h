#ifndef UVM_CFG_ROCKET_RATIO_H
#define UVM_CFG_ROCKET_RATIO_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    bool enabled;
    bool reversed;
    float ratio_p;
    float ratio_n;
} rocket_ratio_propeller_attr;

typedef struct
{
    bool enabled;
    double deadzone_p;
    double deadzone_n;
    rocket_ratio_propeller_attr front_right;
    rocket_ratio_propeller_attr front_left;
    rocket_ratio_propeller_attr center_right;
    rocket_ratio_propeller_attr center_left;
    rocket_ratio_propeller_attr back_right;
    rocket_ratio_propeller_attr back_left;
} rocket_ratio_axis_attr;

typedef struct
{
    rocket_ratio_axis_attr x;
    rocket_ratio_axis_attr y;
    rocket_ratio_axis_attr z;
    rocket_ratio_axis_attr r;
} rocket_ratio_params;

rocket_ratio_params *rocket_ratio_create_with_init_val (void);
void *rocket_ratio_s2j (rocket_ratio_params *params);
rocket_ratio_params *rocket_ratio_j2s (void *json);

#endif
