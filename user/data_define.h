//
// Created by fxf on 23-7-9.
//

#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H

#include "data-type/pid.h"
#include "data-type/device.h"
#include "data-type/rocket.h"
#include "data-type/control.h"
#include "data-type/propeller.h"

typedef struct rov_info {
    struct rocket rocket;
    struct propeller propeller;
    struct pid_scale pidScale;
    struct sensor sensor;
    struct dev_ctl devCtl;
    struct debug_info debugInfo;
    struct rov_thread thread;
} rov_info_t;

#endif //DATA_DEFINE_H
