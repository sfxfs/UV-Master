/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_pca9685_interface_template.c
 * @brief     driver pca9685 interface template source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-02-20
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/02/20  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "interface_pca9685.h"

#include "log.h"
#include "utils/gpio.h"
#include "utils/iic.h"
#include "utils/delay.h"

#include <stdarg.h>

#define PCA9685_I2C_DEV "/dev/i2c-0"
#define PCA9685_GPIO_NUM 203 // PG11 = ( 7 - 1) * 32 + 11

static int pca9685_fd;

/**
 * @brief  interface iic bus init
 * @return status code
 *         - 0 success
 *         - 1 iic init failed
 * @note   none
 */
uint8_t pca9685_interface_iic_init(void)
{
    pca9685_fd = uvm_i2c_init(PCA9685_I2C_DEV);
    if (pca9685_fd < 0)
    {
        log_error("iic dev init failed.");
        return 1;
    }
    return 0;
}

/**
 * @brief  interface iic bus deinit
 * @return status code
 *         - 0 success
 *         - 1 iic deinit failed
 * @note   none
 */
uint8_t pca9685_interface_iic_deinit(void)
{
    if (uvm_i2c_deinit(pca9685_fd) < 0) {
        log_error("iic close fd failed.");
        return 1;
    }
    else
        return 0;
}

/**
 * @brief     interface iic bus write
 * @param[in] addr is the iic device write address
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t pca9685_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (uvm_i2c_write(pca9685_fd, addr, reg, len, buf) < 0) {
        log_error("iic write to device failed.");
        return 1;
    }
    else
        return 0;
}

/**
 * @brief      interface iic bus read
 * @param[in]  addr is the iic device write address
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t pca9685_interface_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (uvm_i2c_read(pca9685_fd, addr, reg, len, buf) < 0) {
        log_error("iic read from device failed.");
        return 1;
    }
    else
        return 0;
}

/**
 * @brief  interface oe init
 * @return status code
 *         - 0 success
 *         - 1 clock init failed
 * @note   none
 */
uint8_t pca9685_interface_oe_init(void)
{
    int ret = uvm_gpio_export_direction(PCA9685_GPIO_NUM, GPIO_DIRECTION_OUTPUT);
    if (ret < 0)
    {
        log_error("gpio device init failed with ret: %s", strerror(ret));
        return 1;
    }
    return 0;
}

/**
 * @brief  interface oe deinit
 * @return status code
 *         - 0 success
 *         - 1 clock deinit failed
 * @note   none
 */
uint8_t pca9685_interface_oe_deinit(void)
{
    if (uvm_gpio_unexport(PCA9685_GPIO_NUM) < 0)
    {
        log_error("gpio dev deinit failed.");
        return 1;
    }
    return 0;
}

/**
 * @brief     interface oe write
 * @param[in] value is the written value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t pca9685_interface_oe_write(uint8_t value)
{
    if (uvm_gpio_set_value(PCA9685_GPIO_NUM, value) < 0)
    {
        log_error("gpio dev set value failed.");
        return 1;
    }
    return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void pca9685_interface_delay_ms(uint32_t ms)
{
    uvm_delay(ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void pca9685_interface_debug_print(const char *const fmt, ...)
{
    va_list temp_va;
	va_start(temp_va, fmt);
	log_error(fmt, temp_va);
	va_end(temp_va);
}
