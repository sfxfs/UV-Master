#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "iic.h"

static inline int i2c_access(int fd, char rw, uint8_t command, int size, union i2c_smbus_data *data)
{
    struct i2c_smbus_ioctl_data args;

    args.read_write = rw;
    args.command = command;
    args.size = size;
    args.data = data;
    return ioctl(fd, I2C_SMBUS, &args);
}

int uvm_i2c_init(char *dev)
{
    int fd = open(dev, O_RDWR);
    if (fd < 0)
    {
        printf("IIC: Fail to open %s \r\n", dev);
        return -1;
    }

    if (ioctl(fd, I2C_TENBIT, 0) < 0) // 7-bit addr
    {
        printf("IIC: Unable to set address type: %s\n", strerror(errno));
        close(fd);
        return -2;
    }

    ioctl(fd, I2C_RETRIES, 5); // ACK retry times
    return fd;
}

int uvm_i2c_deinit(int fd)
{
    return close(fd);
}

int uvm_i2c_write(int fd, uint8_t addr, uint8_t reg, uint8_t len, uint8_t *val)
{
    if (ioctl(fd, I2C_SLAVE, (int)addr) < 0)
    {
        printf("IIC: Unable to select I2C device: %s\n", strerror(errno));
        close(fd);
        return -1;
    }

    union i2c_smbus_data data;

    data.block[0] = len; /* block[0] is used for length */
    if (val)
        memcpy(&data.block[1], val, len);
    return i2c_access(fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_I2C_BLOCK_DATA, &data);
}

int uvm_i2c_read(int fd, uint8_t addr, uint8_t reg, uint8_t len, uint8_t *val)
{
    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        printf("IIC: Unable to select I2C device: %s\n", strerror(errno));
        return -1;
    }

    union i2c_smbus_data data;

    data.block[0] = len;
    if (i2c_access(fd, I2C_SMBUS_READ, reg, I2C_SMBUS_I2C_BLOCK_DATA, &data) != 0) // 请勿使用 I2C_SMBUS_BLOCK_DATA 会导致 SG
        return -1;
    if (val)
        memcpy(val, &data.block[1], len);
    return 0;
}

int uvm_i2c_i2cdetect(int fd, uint8_t addr)
{
    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        printf("IIC: Unable to select I2C device: %s\n", strerror(errno));
        return -1;
    }  
    return 0;
}
