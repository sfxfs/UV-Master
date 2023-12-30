#include <stdio.h>
#include <stdlib.h>

#include "cJSON.h"
#include "s2j.h"

#include "others.h"

static others_params default_params = {
    .server_config = {
        .port = 8888,
        .timeout = 0,
    },
};

others_params *others_create_with_init_val ()
{
    others_params *params_struct = calloc(1, sizeof(others_params));

    if (params_struct)
        *params_struct = default_params;

    return params_struct;
}

static cJSON *struct_to_json_server_attr (server_attr *attr_struct)
{
    s2j_create_json_obj(attr_json);

    s2j_json_set_basic_element(attr_json, attr_struct, int, port);
    s2j_json_set_basic_element(attr_json, attr_struct, int, timeout);

    return attr_json;
}

void *others_s2j (others_params *params)
{
    s2j_create_json_obj(json_params);

    s2j_json_set_struct_element_by_func(json_params, params, server_attr, server_config);

    return json_params;
}

static server_attr *json_to_struct_server_attr(cJSON *attr_json)
{
    s2j_create_struct_obj(attr_struct, server_attr);

    s2j_struct_get_basic_element(attr_struct, attr_json, int, port);
    s2j_struct_get_basic_element(attr_struct, attr_json, int, timeout);

    return attr_struct;
}

others_params *others_j2s (void *json)
{
    s2j_create_struct_obj(params_struct, others_params);
    (void)json_temp;

    s2j_struct_get_struct_element_by_func(params_struct, json, server_attr, server_config);

    return params_struct;
}
