#include <stdio.h>
#include <stdlib.h>

#include "rocket_ratio.h"

static const rocket_ratio_params default_params = {
    .x = {
        .front_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .front_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .center_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .center_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .back_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .back_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
    },
    .y = {
        .front_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .front_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .center_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .center_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .back_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .back_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
    },
    .z = {
        .front_right_attr = {
            .enabled = false,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .front_left_attr = {
            .enabled = false,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .center_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .center_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .back_right_attr = {
            .enabled = false,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .back_left_attr = {
            .enabled = false,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
    },
    .r = {
        .front_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .front_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .center_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .center_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .back_right_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
        .back_left_attr = {
            .enabled = true,
            .reversed = false,
            .ratio_p = 0.3,
            .ratio_n = 0.3,
        },
    },
};

rocket_ratio_params *rocket_ratio_create_with_init_val ()
{
    rocket_ratio_params *params_struct = calloc(1, sizeof(rocket_ratio_params));

    if (params_struct)
        *params_struct = default_params;

    return params_struct;
}

static cJSON *struct_to_json_rocket_ratio_propeller_attr (rocket_ratio_propeller_attr *attr_struct)
{
    s2j_create_json_obj(attr_json);

    s2j_json_set_basic_element(attr_json, attr_struct, bool, enabled);
    s2j_json_set_basic_element(attr_json, attr_struct, bool, reversed);
    s2j_json_set_basic_element(attr_json, attr_struct, double, ratio_p);
    s2j_json_set_basic_element(attr_json, attr_struct, double, ratio_n);

    return attr_json;
}

static cJSON *struct_to_json_rocket_ratio_axis_attr (rocket_ratio_axis_attr *attr_struct)
{
    s2j_create_json_obj(attr_json);

    s2j_json_set_struct_element_by_func(attr_json, attr_struct, rocket_ratio_propeller_attr, front_right_attr);
    s2j_json_set_struct_element_by_func(attr_json, attr_struct, rocket_ratio_propeller_attr, front_left_attr);
    s2j_json_set_struct_element_by_func(attr_json, attr_struct, rocket_ratio_propeller_attr, center_right_attr);
    s2j_json_set_struct_element_by_func(attr_json, attr_struct, rocket_ratio_propeller_attr, center_left_attr);
    s2j_json_set_struct_element_by_func(attr_json, attr_struct, rocket_ratio_propeller_attr, back_right_attr);
    s2j_json_set_struct_element_by_func(attr_json, attr_struct, rocket_ratio_propeller_attr, back_left_attr);

    return attr_json;
}

cJSON *rocket_ratio_s2j (rocket_ratio_params *params)
{
    s2j_create_json_obj(json_params);

    s2j_json_set_struct_element_by_func(json_params, params, rocket_ratio_axis_attr, x);
    s2j_json_set_struct_element_by_func(json_params, params, rocket_ratio_axis_attr, y);
    s2j_json_set_struct_element_by_func(json_params, params, rocket_ratio_axis_attr, z);
    s2j_json_set_struct_element_by_func(json_params, params, rocket_ratio_axis_attr, r);

    return json_params;
}

static rocket_ratio_propeller_attr *json_to_struct_rocket_ratio_propeller_attr(cJSON *attr_json)
{
    s2j_create_struct_obj(attr_struct, rocket_ratio_propeller_attr);

    s2j_struct_get_basic_element(attr_struct, attr_json, int, enabled);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, reversed);
    s2j_struct_get_basic_element(attr_struct, attr_json, double, ratio_p);
    s2j_struct_get_basic_element(attr_struct, attr_json, double, ratio_n);

    return attr_struct;
}

static rocket_ratio_axis_attr *json_to_struct_rocket_ratio_axis_attr(cJSON *attr_json)
{
    s2j_create_struct_obj(attr_struct, rocket_ratio_axis_attr);
    (void)json_temp;

    s2j_struct_get_struct_element_by_func(attr_struct, attr_json, rocket_ratio_propeller_attr, front_right_attr);
    s2j_struct_get_struct_element_by_func(attr_struct, attr_json, rocket_ratio_propeller_attr, front_left_attr);
    s2j_struct_get_struct_element_by_func(attr_struct, attr_json, rocket_ratio_propeller_attr, center_right_attr);
    s2j_struct_get_struct_element_by_func(attr_struct, attr_json, rocket_ratio_propeller_attr, center_left_attr);
    s2j_struct_get_struct_element_by_func(attr_struct, attr_json, rocket_ratio_propeller_attr, back_right_attr);
    s2j_struct_get_struct_element_by_func(attr_struct, attr_json, rocket_ratio_propeller_attr, back_left_attr);

    return attr_struct;
}

rocket_ratio_params *rocket_ratio_j2s (cJSON *json)
{
    s2j_create_struct_obj(params_struct, rocket_ratio_params);
    (void)json_temp;

    s2j_struct_get_struct_element_by_func(params_struct, json, rocket_ratio_axis_attr, x);
    s2j_struct_get_struct_element_by_func(params_struct, json, rocket_ratio_axis_attr, y);
    s2j_struct_get_struct_element_by_func(params_struct, json, rocket_ratio_axis_attr, z);
    s2j_struct_get_struct_element_by_func(params_struct, json, rocket_ratio_axis_attr, r);

    return params_struct;
}
