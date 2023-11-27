#define LOG_TAG "interface.pca9685"

#include <elog.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <gpiod.h>

#include "iic.h"
#include "other_utils.h"

#define PCA9685_I2C_DEV "/dev/i2c-0"        // PCA9685 使用的 I2C设备

#define PCA9685_GPIOCHIP "/dev/gpiochip0"
#define PCA9685_LINE_OFFSET 203 // PG11

static int pca9685_fd;

uint8_t pca9685_interface_iic_init()
{
    pca9685_fd = uvm_i2c_init(PCA9685_I2C_DEV);
    if (pca9685_fd < 0)
    {
        log_e("iic dev init failed");
        return -1;
    }
    return 0;
}

uint8_t pca9685_interface_iic_deinit()
{
    if (uvm_i2c_deinit(pca9685_fd) < 0) {
        log_e("close fd failed");
        return 1;
    }
    else
        return 0;
}

uint8_t pca9685_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (uvm_i2c_write(pca9685_fd, addr, reg, len, buf) < 0) {
        log_e("write to device failed");
        return 1;
    }
    else
        return 0;
}

uint8_t pca9685_interface_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (uvm_i2c_read(pca9685_fd, addr, reg, len, buf) < 0) {
        log_e("read from device failed");
        return 1;
    }
    else
        return 0;
}

uint8_t pca9685_interface_oe_init()
{
    return 0;
}

uint8_t pca9685_interface_oe_deinit()
{
    if (gpiod_ctxless_get_value(PCA9685_GPIOCHIP, PCA9685_LINE_OFFSET, false, NULL) < 0)
    {
        log_e("oe pin deinit failed: %s", strerror(errno));
        return 1;
    }
    return 0;
}

uint8_t pca9685_interface_oe_write(uint8_t value)
{
    if (gpiod_ctxless_set_value(PCA9685_GPIOCHIP, PCA9685_LINE_OFFSET, value, false, NULL, NULL, NULL) < 0)
    {
        log_e("oe pin set to %s failed: %s", value == 1 ? "high" : "low", strerror(errno));
        return 1;
    }
    return 0;
}

void pca9685_interface_delay_ms(uint32_t ms)
{
    uvm_delay(ms);
}

void pca9685_interface_debug_print(const char *const fmt, ...)
{
    va_list temp_va;
	va_start(temp_va, fmt);
	elog_e("device.pca9685", fmt, temp_va);
	va_end(temp_va);
}
