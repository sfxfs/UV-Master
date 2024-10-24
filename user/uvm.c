#include <log.h>
#include <uvm_cfg.h>
#include <uvm_cal.h>
#include "ctrl/mode_manual.h"
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
        exit(EXIT_FAILURE);

    // if (uvm_motor_init(uvm_config.propeller) != 0)
    //     exit(EXIT_FAILURE);

    if (uvm_cal_init(&uvm_cal, uvm_config.others->server_config.port) != 0)
    {
        uvm_motor_deinit();
        exit(EXIT_FAILURE);
    }
    rpc_add_all_handler(&uvm_cal.rpc, &uvm_config);
    uvm_cal_start_thread(&uvm_cal);
    terminal_start_thread();
    manual_ctrl_start_thread(&uvm_config);
}

void uvm_deinit (void)
{
    manual_ctrl_stop_thread();
    terminal_stop_thread();
    uvm_cal_stop_thread(&uvm_cal);
    uvm_motor_deinit();
    uvm_cfg_delete(&uvm_config);
}

void uvm_loop (void)
{

}
