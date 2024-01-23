#ifndef __IIC_H__
#define __IIC_H__

#include <stdint.h>

int uvm_i2c_init(char *dev);
int uvm_i2c_deinit(int fd);
int uvm_i2c_i2cdetect(int fd, uint8_t addr);
int uvm_i2c_write(int fd, uint8_t addr, uint8_t reg, uint8_t len, uint8_t *val);
int uvm_i2c_read(int fd, uint8_t addr, uint8_t reg, uint8_t len, uint8_t *val);

#endif