#include "uart.h"

#include "jy901_interface.h"

#define JY901_DEV "/dev/ttyS1"
#define JY901_BAUDRATE 9600

HARDWARE_UART jy901_uart = {0};

int jy901_interface_uart_init()
{
    if (uvm_uart_begin(&jy901_uart, JY901_DEV) != 0)
        return -1;
    if (uvm_uart_setBaudrate(&jy901_uart, JY901_BAUDRATE) != 0)
        return -1;
    return jy901_uart.fd;
}

void jy901_interface_uart_write(uint8_t *Data, uint32_t Len)
{
    uvm_uart_write(jy901_uart, (char *)Data, Len);
}

uint8_t jy901_interface_uart_read()
{
    return uvm_uart_readByte(jy901_uart);
}

int jy901_interface_uart_avail()
{
    return uvm_uart_data_avail(jy901_uart);
}
