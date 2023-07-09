#define LOG_TAG "server.main"

#include <elog.h>
#include <pthread.h>

#include "../../protocols/jsonrpc-c.h"
#include "handler.h"
#include "server.h"

struct jrpc_server server = {0};

static void info_handler_reg(struct rov_info* info)
{
    jrpc_register_procedure(&server, info_handler, "get_info", NULL);
//    jrpc_register_procedure(&server, debug_info, "get_feedbacks", NULL);
//    jrpc_register_procedure(&server, update, "update_firmware", NULL);
}

static void control_handler_reg(struct rov_info* info)
{
    jrpc_register_procedure(&server, move_asyn_handler, "move_asyn", NULL);
    jrpc_register_procedure(&server, move_syn_handler, "move", NULL);
    jrpc_register_procedure(&server, move_absolute_handler, "move_absolute", NULL);
    jrpc_register_procedure(&server, move_relative_handler, "move_relative", NULL);
//    jrpc_register_procedure(&server, catcher, "catch", NULL);
//    jrpc_register_procedure(&server, depth, "depth", NULL);
//    jrpc_register_procedure(&server, direction_lock, "set_direction_locked", NULL);
//    jrpc_register_procedure(&server, depth_lock, "set_depth_locked", NULL);
}

static void debug_handler_reg(struct rov_info* info)
{
//    jrpc_register_procedure(&server, set_debug_mode_enabled, "set_debug_mode_enabled", NULL);
//    jrpc_register_procedure(&server, set_propeller_pwm_freq_calibration, "set_propeller_pwm_freq_calibration", NULL);
//    jrpc_register_procedure(&server, set_propeller_values, "set_propeller_values", NULL);
//    jrpc_register_procedure(&server, set_propeller_parameters, "set_propeller_parameters", NULL);
//    jrpc_register_procedure(&server, set_control_loop_parameters, "set_control_loop_parameters", NULL);
//    jrpc_register_procedure(&server, load, "load_parameters", NULL);
//    jrpc_register_procedure(&server, save, "save_parameters", NULL);
}

void *server_thread(void *arg)
{
    rov_info_t *info = (rov_info_t *)arg;

    info_handler_reg(info);
    control_handler_reg(info);
    debug_handler_reg(info);

    jrpc_server_run(&server);
    //running...
    jrpc_server_destroy(&server);
    return 0;
}

int jsonrpc_server_run(struct rov_info* info, int port)
{
    if (jrpc_server_init(&server, port) != 0) {
        log_e("init failed");
        return -1;
    }
    log_i("starting thread");
    pthread_t server_tid;
    pthread_create(&server_tid, NULL, server_thread, info);
    pthread_detach(server_tid);
    return 0;
}

int jsonrpc_server_stop()
{
    log_i("stop service");
    return jrpc_server_stop(&server);
}
