#ifndef _GPIO_FS_H_
#define _GPIO_FS_H_

#include <stdbool.h>
#include <stdint.h>

enum gpio_direction
{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT,
};

int rov_gpio_export(uint32_t gpio);
int rov_gpio_unexport(uint32_t gpio);
int rov_gpio_set_direction(uint32_t gpio, enum gpio_direction input);
int rov_gpio_get_direction(uint32_t gpio);
int rov_gpio_export_direction(uint32_t gpio, enum gpio_direction input);
int rov_gpio_set_value(uint32_t gpio, int value);
int rov_gpio_get_value(uint32_t gpio);

#endif
