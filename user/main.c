#include <log.h>
#include <uvm_cfg.h>
#include <uvm_cal.h>
#include "rpc/rpc_fun.h"
#include "dev/motor.h"

config_data uvm_config;
uvm_cal_t uvm_cal;

int main(int argc, char **argv)
{
    // log_set_level(LOG_INFO);
    uvm_config = uvm_cfg_init();
    if (uvm_config.read_succeed != true)
    {
        log_error("load config file failed.");
        return -1;
    }
    if (uvm_motor_init(uvm_config.propeller) != 0)
    {
        log_error("motor init failed.");
        return -1;
    }
    if (uvm_cal_init(&uvm_cal, uvm_config.others->server_config.port) != 0)
    {
        log_error("cal init failed.");
        return -1;
    }
    rpc_add_all_handler(&uvm_cal.rpc, &uvm_config);
    uvm_cal_start_thread(&uvm_cal);
    for (;;);
    return 0;
}
