#ifndef INTERFACE_PCA9685_H
#define INTERFACE_PCA9685_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

uint8_t pca9685_interface_iic_init      ();
uint8_t pca9685_interface_iic_deinit    ();
uint8_t pca9685_interface_iic_write     (uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);
uint8_t pca9685_interface_iic_read      (uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);
uint8_t pca9685_interface_oe_init       ();
uint8_t pca9685_interface_oe_deinit     ();
uint8_t pca9685_interface_oe_write      (uint8_t value);
void    pca9685_interface_delay_ms      (uint32_t ms);
void    pca9685_interface_debug_print   (const char *const fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
