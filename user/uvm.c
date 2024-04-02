#include <log.h>
#include <uvm_cfg.h>
#include <uvm_cal.h>
#include "rpc/rpc_fun.h"
#include "dev/motor.h"
#include "term/terminal.h"

#include <stdlib.h>

config_data uvm_config;
uvm_cal_t uvm_cal;

void uvm_init (unsigned char debug_level)
{
    if (debug_level > LOG_FATAL)
        log_set_quiet(true);
    else
        log_set_level(debug_level);

    if (uvm_cfg_init(&uvm_config) != 0)
    {
        log_error("load config file failed.");
        exit(EXIT_FAILURE);
    }
    if (uvm_motor_init(uvm_config.propeller) != 0)
    {
        log_error("motor init failed.");
        exit(EXIT_FAILURE);
    }
    if (uvm_cal_init(&uvm_cal, uvm_config.others->server_config.port) != 0)
    {
        log_error("cal init failed.");
        uvm_motor_deinit();
        exit(EXIT_FAILURE);
    }
    rpc_add_all_handler(&uvm_cal.rpc, &uvm_config);
    uvm_cal_start_thread(&uvm_cal);
    terminal_start_thread();
}

void uvm_deinit (void)
{
    uvm_cal_stop_thread(&uvm_cal);
    uvm_motor_deinit();
    uvm_cfg_delete(&uvm_config);
}

void uvm_loop (void)
{

}
