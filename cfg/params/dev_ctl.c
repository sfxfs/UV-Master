#include "dev_ctl.h"

void dev_ctl_init_val (struct dev_ctl_params *params)
{
    for (size_t i = 0; i < DEV_NUM; i++)
    {
        params->attr[i].channel = 0;
        params->attr[i].enabled = false;
        params->attr[i].nMax = 500;
        params->attr[i].pMax = 2500;
        params->attr[i].reset = 1500;
        params->attr[i].step = 100;
    }
}

static cJSON *dev_ctl_s2j_attr (struct dev_ctl_attr *attr)
{
    s2j_create_json_obj(json_attr);

    s2j_json_set_basic_element(json_attr, attr, bool, enabled);
}

cJSON *dev_ctl_s2j (struct dev_ctl_params *params)
{
    
}
