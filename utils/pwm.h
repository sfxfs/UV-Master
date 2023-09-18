#ifndef __PWM_H__
#define __PWM_H__

#include <stdbool.h>
#include <stdint.h>

enum pwm_polarity {
        PWM_POLARITY_NORMAL,
        PWM_POLARITY_INVERSED,
};

int rov_pwm_export(uint32_t pwm);
int rov_pwm_unexport(uint32_t pwm);
int rov_pwm_set_period(uint32_t pwm, uint32_t period);
int rov_pwm_get_period(uint32_t pwm);
int rov_pwm_set_duty(uint32_t pwm, uint32_t duty);
int rov_pwm_get_duty(uint32_t pwm);
int rov_pwm_set_polarity(uint32_t pwm, enum pwm_polarity polarity);
int rov_pwm_get_polarity(uint32_t pwm);
int rov_pwm_set_enable(uint32_t pwm, bool enabled);
int rov_pwm_get_enable(uint32_t pwm);
int rov_pwm_init(uint32_t pwm, uint32_t period, uint32_t duty,
		   enum pwm_polarity polarity);
int rov_pwm_deinit(uint32_t pwm);

#endif
