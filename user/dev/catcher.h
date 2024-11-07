#ifndef _UVM_SRC_DEV_CATCHER_H_
#define _UVM_SRC_DEV_CATCHER_H_

#include <cfg_dev_ctl.h>

int uvm_catcher_init(dev_ctl_attr *cfg);
int uvm_catcher_deinit(dev_ctl_attr *cfg);
int uvm_catcher_write(dev_ctl_attr *cfg, int req);

#endif
