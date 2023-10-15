#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <i2c/smbus.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "iic.h"

int uvm_i2c_init(char *dev)
{
    int fd = open(dev, O_RDWR);
    if (fd < 0)
    {
        printf("fail to open %s \r\n", dev);
        return -1;
    }
    return fd;
}
int uvm_i2c_deinit(int fd)
{
    return close(fd);
}

int uvm_i2c_write(int fd, uint8_t addr, uint8_t reg, uint8_t len, uint8_t *val)
{
    if (ioctl(fd, I2C_TENBIT, 0) < 0)
    {
        printf("Unable to set address type: %s\n", strerror(errno));
        close(fd);
        return -1;
    } 

    if (ioctl(fd, I2C_SLAVE, (int)addr) < 0)
    {
        printf("Unable to select I2C device: %s\n", strerror(errno));
        close(fd);
        return -1;
    }

    ioctl(fd, I2C_RETRIES, 5);

    return i2c_smbus_write_i2c_block_data(fd, reg, len, val);
}

int uvm_i2c_read(int fd, uint8_t addr, uint8_t reg, uint8_t len, uint8_t *val)
{
    ioctl(fd, I2C_TENBIT, 0);

    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        printf("Unable to select I2C device: %s\n", strerror(errno));
        return -1;
    }

    ioctl(fd, I2C_RETRIES, 5);

    return i2c_smbus_read_i2c_block_data(fd, reg, len, val);
}

int uvm_i2c_write_byte(int fd, uint8_t addr, uint8_t reg, uint8_t val)
{
    // int retries;
    uint8_t data[2];

    data[0] = reg;
    data[1] = val;

    ioctl(fd, I2C_TENBIT, 0);

    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        printf("Unable to select I2C device: %s\n", strerror(errno));
        return -1;
    }

    ioctl(fd, I2C_RETRIES, 5);

    if (write(fd, data, 2) == 2)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int uvm_i2c_read_byte(int fd, uint8_t addr, uint8_t reg, uint8_t *val)
{
    // int retries;
    ioctl(fd, I2C_TENBIT, 0);
    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        printf("Unable to select I2C device: %s\n", strerror(errno));
        return -1;
    }
    ioctl(fd, I2C_RETRIES, 5);

    if (write(fd, &reg, 1) == 1)
    {
        if (read(fd, val, 1) == 1)
        {
            return 0;
        }
    }

    return -1;
}

int uvm_i2c_i2cdetect(int fd, uint8_t addr)
{
    ioctl(fd, I2C_TENBIT, 0);
    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        printf("Unable to select I2C device: %s\n", strerror(errno));
        return -1;
    }  
    return 0;
}
