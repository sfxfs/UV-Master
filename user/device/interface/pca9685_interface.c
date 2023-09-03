#define LOG_TAG "interface.pca9685"

#include <elog.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <gpiod.h>
#include <fcntl.h>

#define PCA9685_I2C_DEV "/dev/i2c-0"        // PCA9685 使用的 I2C设备
#define PCA9685_I2C_7BIT_ADDR 0x40          // 将A0-A5全部接地，则其器件地址为:0x40
#define PCA9685_GPIOCHIP "/dev/gpiochip0"
static const unsigned int pca9685_line_offset = 1;

int pca9685_fd;
struct gpiod_line_request *request = NULL;

uint8_t pca9685_interface_iic_init()
{
    pca9685_fd = open(PCA9685_I2C_DEV, O_RDWR);
    if (!pca9685_fd)
    {
        log_e("cannot get fd");
        return 1;
    }
    if(ioctl(pca9685_fd, I2C_SLAVE, PCA9685_I2C_7BIT_ADDR) < 0)
    {
        log_e("cannot set interface to slave mode");
        return 2;
    }
    return 0;
}

uint8_t pca9685_interface_iic_deinit()
{
    if (close(pca9685_fd) < 0) {
        log_e("close fd failed");
        return 1;
    }
    else
        return 0;
}

uint8_t pca9685_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (i2c_smbus_write_i2c_block_data(pca9685_fd, reg, len, buf) < 0) {
        log_e("write to device failed");
        return 1;
    }
    else
        return 0;
}

uint8_t pca9685_interface_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (i2c_smbus_read_i2c_block_data(pca9685_fd, reg, len, buf) < 0) {
        log_e("read from device failed");
        return 1;
    }
    else
        return 0;
}

uint8_t pca9685_interface_oe_init()
{
    struct gpiod_request_config *req_cfg = NULL;
    struct gpiod_line_settings *settings;
    struct gpiod_line_config *line_cfg;
    struct gpiod_chip *chip;
    int ret;

    chip = gpiod_chip_open(PCA9685_GPIOCHIP);
    if (!chip)
        return -1;

    settings = gpiod_line_settings_new();
    if (!settings)
        goto close_chip;

    gpiod_line_settings_set_direction(settings,
                                      GPIOD_LINE_DIRECTION_OUTPUT);
    gpiod_line_settings_set_output_value(settings, GPIOD_LINE_VALUE_ACTIVE);

    line_cfg = gpiod_line_config_new();
    if (!line_cfg)
        goto free_settings;

    ret = gpiod_line_config_add_line_settings(line_cfg, &pca9685_line_offset, 1,
                                              settings);
    if (ret)
        goto free_line_config;

    request = gpiod_chip_request_lines(chip, req_cfg, line_cfg);

    gpiod_request_config_free(req_cfg);

free_line_config:
    gpiod_line_config_free(line_cfg);

free_settings:
    gpiod_line_settings_free(settings);

close_chip:
    gpiod_chip_close(chip);

    return 0;
}

uint8_t pca9685_interface_oe_deinit()
{
    gpiod_line_request_release(request);
    return 0;
}

uint8_t pca9685_interface_oe_write(uint8_t value)
{
    gpiod_line_request_set_value(request, pca9685_line_offset, value);
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
