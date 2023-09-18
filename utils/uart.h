#ifndef __UART_
#define __UART_

#include <stdint.h>
#include <termios.h>

typedef struct UARTStruct {
    int fd;
    struct termios set;
} HARDWARE_UART;

int rov_uart_begin(HARDWARE_UART *dev, char *UART_device);
int rov_uart_end(HARDWARE_UART *dev);
int rov_uart_setBaudrate(HARDWARE_UART *dev, uint32_t Baudrate);

int rov_uart_write(HARDWARE_UART *dev, const char * buf, uint32_t len);
int rov_uart_read(HARDWARE_UART *dev, char* buf, uint32_t len);
int rov_uart_writeByte(HARDWARE_UART *dev, uint8_t buf);
int rov_uart_readByte(HARDWARE_UART *dev);

int rov_uart_Set(HARDWARE_UART *dev, int databits, int stopbits, int parity);

#endif
