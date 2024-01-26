#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>
#include <stddef.h>

typedef struct SPIStruct {
    int fd;
    uint32_t max_speed;
    uint8_t bits;
} HARDWARE_SPI;

int uvm_spi_init(HARDWARE_SPI *spi, char *dev, uint32_t mode, uint8_t bits, uint32_t speed);
int uvm_spi_deinit(HARDWARE_SPI *spi);
int uvm_spi_transfer(HARDWARE_SPI *spi, uint8_t const *tx, uint8_t const *rx, size_t len,uint16_t delay);

#endif
