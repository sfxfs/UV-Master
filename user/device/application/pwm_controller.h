#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H

#include "pca9685.h"

int pwm_controller_init     (pca9685_address_t addr, uint16_t hz);
int pwm_controller_deinit   (void);
int pwm_controller_write    (pca9685_channel_t channel, float delay_percent, float high_duty_cycle_percent);

#endif
