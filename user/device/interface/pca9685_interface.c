#define LOG_TAG "interface.pca9685"

#include <elog.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#include "iic.h"
#include "gpio_gpiod.h"

#define PCA9685_I2C_DEV "/dev/i2c-0"        // PCA9685 使用的 I2C设备
#define PCA9685_I2C_7BIT_ADDR 0x40          // 将A0-A5全部接地，则其器件地址为:0x40
#define PCA9685_GPIOCHIP "/dev/gpiochip0"
static const unsigned int PCA9685_LINE = 1;

int pca9685_fd;
struct gpiod_line_request *request = NULL;

uint8_t pca9685_interface_iic_init()
{
    if (rov_i2c_init(PCA9685_I2C_DEV) < 0)
    {
        log_e("iic dev init failed");
        return -1;
    }
    return 0;
}

uint8_t pca9685_interface_iic_deinit()
{
    if (rov_i2c_deinit(pca9685_fd) < 0) {
        log_e("close fd failed");
        return 1;
    }
    else
        return 0;
}

uint8_t pca9685_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (rov_i2c_write(pca9685_fd, addr, reg, len, buf) < 0) {
        log_e("write to device failed");
        return 1;
    }
    else
        return 0;
}

uint8_t pca9685_interface_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (rov_i2c_read(pca9685_fd, addr, reg, len, buf) < 0) {
        log_e("read from device failed");
        return 1;
    }
    else
        return 0;
}

uint8_t pca9685_interface_oe_init()
{
    request = gpio_set_output_mode(PCA9685_GPIOCHIP, PCA9685_LINE, GPIOD_LINE_VALUE_INACTIVE, NULL);
    return 0;
}

uint8_t pca9685_interface_oe_deinit()
{
    gpio_deinit(request);
    return 0;
}

uint8_t pca9685_interface_oe_write(uint8_t value)
{
    gpio_set_output_value(request, PCA9685_LINE, value);
    return 0;
}

void pca9685_interface_delay_ms(uint32_t ms)
{
    usleep(ms * 1000);
}

void pca9685_interface_debug_print(const char *const fmt, ...)
{
    va_list temp_va;
	va_start(temp_va, fmt);
	elog_d("device.pca9685", fmt, temp_va);
	va_end(temp_va);
}
