#ifndef DRIVER_JY901_INTERFACE_H
#define DRIVER_JY901_INTERFACE_H

#include <stdint.h>

int jy901_interface_uart_init();

void jy901_interface_uart_write(uint8_t *Data, uint32_t Len);\

uint8_t jy901_interface_uart_read();

int jy901_interface_uart_avail();

#endif
