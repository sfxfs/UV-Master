#ifndef UVM_CFG_H
#define UVM_CFG_H

#include "cfg_others.h"
#include "cfg_dev_ctl.h"
#include "cfg_propeller.h"
#include "cfg_rocket_ratio.h"

typedef struct
{
    propeller_params *propeller;
    dev_ctl_params *dev_ctl;
    rocket_ratio_params *rocket_ratio;
    others_params *others;
} config_data;

/* ess */
void    uvm_cfg_delete(config_data *data_s);
int     uvm_cfg_init  (config_data *data_s);
int     uvm_cfg_read  (config_data *data_s);
int     uvm_cfg_write (config_data *data_s);

/* add */
// int uvm_cfg_read_cjson (void *cjson);
// int uvm_cfg_write_cjson (void *cjson);

#endif
