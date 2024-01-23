#include <stdio.h>
#include <stdlib.h>

#include "cjson/cJSON.h"
#include "cjson/s2j.h"

#include "dev_ctl.h"

static const dev_ctl_params default_params = {
    .arm_attr = {
        .channel = 6,
        .enabled = false,
        .nMax = 500,
        .pMax = 2500,
        .reset = 1500,
        .step = 100,
    },
    .light_attr = {
        .channel = 7,
        .enabled = false,
        .nMax = 500,
        .pMax = 2500,
        .reset = 1500,
        .step = 100,
    },
};

dev_ctl_params *dev_ctl_create_with_init_val ()
{
    dev_ctl_params *params_struct = calloc(1, sizeof(dev_ctl_params));

    if (params_struct)
        *params_struct = default_params;

    return params_struct;
}

static cJSON *struct_to_json_dev_ctl_attr (dev_ctl_attr *attr_struct)
{
    s2j_create_json_obj(attr_json);

    s2j_json_set_basic_element(attr_json, attr_struct, bool, enabled);
    s2j_json_set_basic_element(attr_json, attr_struct, int, channel);
    s2j_json_set_basic_element(attr_json, attr_struct, int, pMax);
    s2j_json_set_basic_element(attr_json, attr_struct, int, nMax);
    s2j_json_set_basic_element(attr_json, attr_struct, int, reset);
    s2j_json_set_basic_element(attr_json, attr_struct, int, step);

    return attr_json;
}

void *dev_ctl_s2j (dev_ctl_params *params)
{
    s2j_create_json_obj(json_params);

    s2j_json_set_struct_element_by_func(json_params, params, dev_ctl_attr, arm_attr);
    s2j_json_set_struct_element_by_func(json_params, params, dev_ctl_attr, light_attr);

    return json_params;
}

static dev_ctl_attr *json_to_struct_dev_ctl_attr(cJSON *attr_json)
{
    s2j_create_struct_obj(attr_struct, dev_ctl_attr);

    s2j_struct_get_basic_element(attr_struct, attr_json, int, enabled);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, channel);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, pMax);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, nMax);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, reset);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, step);

    return attr_struct;
}

dev_ctl_params *dev_ctl_j2s (void *json)
{
    s2j_create_struct_obj(params_struct, dev_ctl_params);
    (void)json_temp;

    s2j_struct_get_struct_element_by_func(params_struct, json, dev_ctl_attr, arm_attr);
    s2j_struct_get_struct_element_by_func(params_struct, json, dev_ctl_attr, light_attr);

    return params_struct;
}
