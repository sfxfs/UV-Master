#define LOG_TAG "interface.pca9685"

#include <elog.h>
#include <stdio.h>
#include <stdarg.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define PCA9685_I2C_DEV "/dev/i2c-0"        // PCA9685 使用的 I2C设备
#define PCA9685_I2C_7BIT_ADDR 0x40          // 将A0-A5全部接地，则其器件地址为:0x40
#define PCA9685_OE_PIN 7                    // 芯片使能引脚 -> GPIO11引脚序号为 7

static pca9685_fd;

uint8_t pca9685_interface_iic_init()
{
    pca9685_fd = wiringPiI2CSetupInterface(PCA9685_I2C_DEV, PCA9685_I2C_7BIT_ADDR);
    if (pca9685_fd)
        return 0;
    else
        return 1;
}

uint8_t pca9685_interface_iic_deinit()
{
    if (close(pca9685_fd) < 0)
        return 1;
    else
        return 0;
}

uint8_t pca9685_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (i2c_smbus_write_block_data(pca9685_fd, reg, len, buf) < 0)
        return 1;
    else
        return 0;
}

uint8_t pca9685_interface_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (i2c_smbus_read_i2c_block_data(pca9685_fd, reg, len, buf) < 0)
        return 1;
    else
        return 0;
}

uint8_t pca9685_interface_oe_init()
{
    pinMode(PCA9685_OE_PIN, OUTPUT);
    return 0;
}

uint8_t pca9685_interface_oe_deinit()
{
    return 0;
}

uint8_t pca9685_interface_oe_write(uint8_t value)
{
    digitalWrite(PCA9685_OE_PIN, value);
    return 0;
}

void pca9685_interface_delay_ms(uint32_t ms)
{
    delay(ms);
}

void pca9685_interface_debug_print(const char *const fmt, ...)
{
    va_list temp_va;
	va_start(temp_va, fmt);
	elog_d(fmt, temp_va);
	va_end(temp_va);
}
