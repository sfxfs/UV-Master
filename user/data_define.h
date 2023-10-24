//
// Created by fxf on 23-7-9.
//

#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H

#include "data-type/system.h"
#include "data-type/device.h"
#include "data-type/rocket.h"
#include "data-type/control.h"
#include "data-type/propeller.h"

typedef struct rov_info {
    control_t control;
    system_t system;
    propeller_t propeller;
    rocket_t rocket;
    device_t device;
} rov_info_t;

#endif //DATA_DEFINE_H
