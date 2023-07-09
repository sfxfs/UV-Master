#define LOG_TAG "server.main"

#include <elog.h>
#include <pthread.h>

#include "../../protocols/jsonrpc-c.h"
#include "handler.h"
#include "server.h"

struct jrpc_server server = {0};
rov_info_t *info_ptr = NULL;

static void info_handler_reg()
{
    jrpc_register_procedure(&server, info_handler, "get_info", NULL);
//    jrpc_register_procedure(&server, debug_info, "get_feedbacks", NULL);
//    jrpc_register_procedure(&server, update, "update_firmware", NULL);
}

static void control_handler_reg()
{
//    jrpc_register_procedure(&server, move_asyn, "move_asyn", NULL);
//    jrpc_register_procedure(&server, move_syn, "move", NULL);
//    jrpc_register_procedure(&server, catcher, "catch", NULL);
//    jrpc_register_procedure(&server, depth, "depth", NULL);
//    jrpc_register_procedure(&server, move_absolute, "move_absolute", NULL);
//    jrpc_register_procedure(&server, move_relative, "move_relative", NULL);
//    jrpc_register_procedure(&server, direction_lock, "set_direction_locked", NULL);
//    jrpc_register_procedure(&server, depth_lock, "set_depth_locked", NULL);
}

static void debug_handler_reg()
{
//    jrpc_register_procedure(&server, set_debug_mode_enabled, "set_debug_mode_enabled", NULL);
//    jrpc_register_procedure(&server, set_propeller_pwm_freq_calibration, "set_propeller_pwm_freq_calibration", NULL);
//    jrpc_register_procedure(&server, set_propeller_values, "set_propeller_values", NULL);
//    jrpc_register_procedure(&server, set_propeller_parameters, "set_propeller_parameters", NULL);
//    jrpc_register_procedure(&server, set_control_loop_parameters, "set_control_loop_parameters", NULL);
//    jrpc_register_procedure(&server, load, "load_parameters", NULL);
//    jrpc_register_procedure(&server, save, "save_parameters", NULL);
}

static void *server_thread(void *arg)
{
    jrpc_server_run(&server);
    //running...
    jrpc_server_destroy(&server);
    return 0;
}

int jsonrpc_server_run(struct rov_info* info, int port)
{
    pthread_t server_tid;
    info_ptr = info;

    if (jrpc_server_init(&server, port) != 0) {
        log_e("init failed");
        return -1;
    }
    info_handler_reg();
    control_handler_reg();
    debug_handler_reg();

    log_i("starting thread");
    pthread_create(&server_tid, NULL, server_thread, NULL);
    pthread_detach(server_tid);
    return 0;
}

int jsonrpc_server_stop()
{
    return jrpc_server_stop(&server);
}
