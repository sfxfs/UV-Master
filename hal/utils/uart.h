#ifndef __UART_
#define __UART_

#include <stdint.h>
#include <termios.h>

typedef struct UARTStruct {
    int fd;
    struct termios set;
} HARDWARE_UART;

int uvm_uart_begin(HARDWARE_UART *dev, char *UART_device);
int uvm_uart_end(HARDWARE_UART dev);
int uvm_uart_setBaudrate(HARDWARE_UART *dev, uint32_t Baudrate);

int uvm_uart_write(HARDWARE_UART dev, const char * buf, uint32_t len);
int uvm_uart_read(HARDWARE_UART dev, char* buf, uint32_t len);
int uvm_uart_writeByte(HARDWARE_UART dev, uint8_t buf);
int uvm_uart_readByte(HARDWARE_UART dev);
int uvm_uart_data_avail(HARDWARE_UART dev);

int uvm_uart_Set(HARDWARE_UART *dev, int databits, int stopbits, int parity);

#endif
