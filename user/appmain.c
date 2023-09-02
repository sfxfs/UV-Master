//
// Created by fxf on 23-9-2.
//

#define LOG_TAG "rov.main"

#include <unistd.h>
#include "server/server.h"

rov_info_t rovInfo = {0};

void setup()
{
    jsonrpc_server_run(&rovInfo, 8888);
}

void loop()
{
    sleep(1);
}
