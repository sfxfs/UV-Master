#ifndef UVM_CFG_H
#define UVM_CFG_H

#include "params/others.h"
#include "params/dev_ctl.h"
#include "params/propeller.h"
#include "params/rocket_ratio.h"

typedef struct
{
    bool read_succeed;
    propeller_params *propeller;
    dev_ctl_params *dev_ctl;
    rocket_ratio_params *rocket_ratio;
    others_params *others;
} config_data;

/* ess */
void        uvm_cfg_free  (config_data data_s);
config_data uvm_cfg_init  (void);
config_data uvm_cfg_read  (void);
int         uvm_cfg_write (config_data data_s);

/* add */
int uvm_cfg_read_cjson (void *cjson);
int uvm_cfg_write_cjson (void *cjson);

#endif
