#include "uart.h"

#include "jy901_interface.h"

#define JY901_DEV "/dev/ttyS1"
#define JY901_BAUDRATE 9600

HARDWARE_UART jy901_uart = {0};

int jy901_interface_uart_init()
{
    if (rov_uart_begin(&jy901_uart, JY901_DEV) != 0)
        return -1;
    if (rov_uart_setBaudrate(&jy901_uart, JY901_BAUDRATE) != 0)
        return -1;
    return 0;
}

void jy901_interface_uart_write(uint8_t *Data, uint32_t Len)
{
    rov_uart_write(&jy901_uart, (char *)Data, Len);
}
