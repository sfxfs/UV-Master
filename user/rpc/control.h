#ifndef _UVM_SRC_RPC_CTRL_H_
#define _UVM_SRC_RPC_CTRL_H_

#include "uvm_cfg.h"

typedef struct
{
    bool updated;
    double x;
    double y;
    double z;
    double rot;
} rocket_raw_t;

void rpc_manual_ctrl(config_data *cfg, double x, double y, double z, double r);

#endif
