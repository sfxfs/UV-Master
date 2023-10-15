#ifndef _GPIO_FS_H_
#define _GPIO_FS_H_

#include <stdbool.h>
#include <stdint.h>

enum gpio_direction
{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT,
};

int uvm_gpio_export(uint32_t gpio);
int uvm_gpio_unexport(uint32_t gpio);
int uvm_gpio_set_direction(uint32_t gpio, enum gpio_direction input);
int uvm_gpio_get_direction(uint32_t gpio);
int uvm_gpio_export_direction(uint32_t gpio, enum gpio_direction input);
int uvm_gpio_set_value(uint32_t gpio, int value);
int uvm_gpio_get_value(uint32_t gpio);

#endif
