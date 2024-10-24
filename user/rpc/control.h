#ifndef _UVM_SRC_RPC_CTRL_H_
#define _UVM_SRC_RPC_CTRL_H_

#include "uvm_cfg.h"

typedef enum
{
    CATCH_CLOSE = -1,
    CATCH_NOACT,
    CATCH_OPEN,
} catch_stat_t;

typedef struct
{
    bool updated;
    double x;
    double y;
    double z;
    double rot;
    catch_stat_t catch;
} rocket_raw_t;

void rpc_manual_ctrl(config_data *cfg, double x, double y, double z, double r);
void catch_ctrl(double val);

#endif
