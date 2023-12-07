#ifndef UVM_CFG_H
#define UVM_CFG_H

#include "uvm-cfg-def.h"

/* ess */
int uvm_cfg_init  (struct config_data *data_s);
int uvm_cfg_read  (struct config_data *data_s);
int uvm_cfg_write (struct config_data *data_s);

/* add */
int uvm_cfg_read_cjson (void *cjson);
int uvm_cfg_write_cjson (void *cjson);

#endif
