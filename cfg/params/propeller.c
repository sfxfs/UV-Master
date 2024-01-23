#include <stdio.h>
#include <stdlib.h>

#include "cjson/cJSON.h"
#include "cjson/s2j.h"

#include "propeller.h"

static const propeller_params default_params = {
    .pwm_freq_offset = 0,
    .front_right_attr = {
        .channel = 0,
        .enabled = true,
        .reversed = false,
        .deadzone_upper = 25,
        .deadzone_lower = -25,
        .power_positive = 0.5,
        .power_negative = 0.5,
    },
    .front_left_attr = {
        .channel = 1,
        .enabled = true,
        .reversed = false,
        .deadzone_upper = 25,
        .deadzone_lower = -25,
        .power_positive = 0.5,
        .power_negative = 0.5,
    },
    .center_right_attr = {
        .channel = 2,
        .enabled = true,
        .reversed = false,
        .deadzone_upper = 25,
        .deadzone_lower = -25,
        .power_positive = 0.5,
        .power_negative = 0.5,
    },
    .center_left_attr = {
        .channel = 3,
        .enabled = true,
        .reversed = false,
        .deadzone_upper = 25,
        .deadzone_lower = -25,
        .power_positive = 0.5,
        .power_negative = 0.5,
    },
    .back_right_attr = {
        .channel = 4,
        .enabled = true,
        .reversed = false,
        .deadzone_upper = 25,
        .deadzone_lower = -25,
        .power_positive = 0.5,
        .power_negative = 0.5,
    },
    .back_left_attr = {
        .channel = 5,
        .enabled = true,
        .reversed = false,
        .deadzone_upper = 25,
        .deadzone_lower = -25,
        .power_positive = 0.5,
        .power_negative = 0.5,
    },
};

propeller_params *propeller_create_with_init_val ()
{
    propeller_params *params_struct = calloc(1, sizeof(propeller_params));

    if (params_struct)
        *params_struct = default_params;

    return params_struct;
}

static cJSON *struct_to_json_propeller_attr (propeller_attr *attr_struct)
{
    s2j_create_json_obj(attr_json);

    s2j_json_set_basic_element(attr_json, attr_struct, bool, reversed);
    s2j_json_set_basic_element(attr_json, attr_struct, bool, enabled);
    s2j_json_set_basic_element(attr_json, attr_struct, int, channel);
    s2j_json_set_basic_element(attr_json, attr_struct, int, deadzone_upper);
    s2j_json_set_basic_element(attr_json, attr_struct, int, deadzone_lower);
    s2j_json_set_basic_element(attr_json, attr_struct, double, power_positive);
    s2j_json_set_basic_element(attr_json, attr_struct, double, power_negative);

    return attr_json;
}

void *propeller_s2j (propeller_params *params)
{
    s2j_create_json_obj(json_params);

    s2j_json_set_basic_element(json_params, params, int, pwm_freq_offset);
    s2j_json_set_struct_element_by_func(json_params, params, propeller_attr, front_right_attr);
    s2j_json_set_struct_element_by_func(json_params, params, propeller_attr, front_left_attr);
    s2j_json_set_struct_element_by_func(json_params, params, propeller_attr, center_right_attr);
    s2j_json_set_struct_element_by_func(json_params, params, propeller_attr, center_left_attr);
    s2j_json_set_struct_element_by_func(json_params, params, propeller_attr, back_right_attr);
    s2j_json_set_struct_element_by_func(json_params, params, propeller_attr, back_left_attr);

    return json_params;
}

static propeller_attr *json_to_struct_propeller_attr(cJSON *attr_json)
{
    s2j_create_struct_obj(attr_struct, propeller_attr);

    s2j_struct_get_basic_element(attr_struct, attr_json, int, reversed);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, enabled);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, channel);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, deadzone_upper);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, deadzone_lower);
    s2j_struct_get_basic_element(attr_struct, attr_json, double, power_positive);
    s2j_struct_get_basic_element(attr_struct, attr_json, double, power_negative);

    return attr_struct;
}

propeller_params *propeller_j2s (void *json)
{
    s2j_create_struct_obj(params_struct, propeller_params);
    (void)json_temp;

    s2j_struct_get_basic_element(params_struct, json, int, pwm_freq_offset);
    s2j_struct_get_struct_element_by_func(params_struct, json, propeller_attr, front_right_attr);
    s2j_struct_get_struct_element_by_func(params_struct, json, propeller_attr, front_left_attr);
    s2j_struct_get_struct_element_by_func(params_struct, json, propeller_attr, center_right_attr);
    s2j_struct_get_struct_element_by_func(params_struct, json, propeller_attr, center_left_attr);
    s2j_struct_get_struct_element_by_func(params_struct, json, propeller_attr, back_right_attr);
    s2j_struct_get_struct_element_by_func(params_struct, json, propeller_attr, back_left_attr);

    return params_struct;
}
