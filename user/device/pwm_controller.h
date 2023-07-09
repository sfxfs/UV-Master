#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H

#include "../../drivers/pca9685.h"

#define PCA9685_BASIC_DEFAULT_RESPOND_SUBADDRESS_1        PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_RESPOND_SUBADDRESS_2        PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_RESPOND_SUBADDRESS_2        PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_RESPOND_ALL_CALL            PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_OUTPUT_INVERT               PCA9685_BOOL_FALSE                                /**< disable */
#define PCA9685_BASIC_DEFAULT_OUTPUT_CHANGE               PCA9685_OUTPUT_CHANGE_STOP                        /**< stop change */
#define PCA9685_BASIC_DEFAULT_OUTPUT_DRIVER               PCA9685_OUTPUT_DRIVER_TOTEM_POLE                  /**< totem pole */
#define PCA9685_BASIC_DEFAULT_OUTPUT_DISABLE_TYPE         PCA9685_OUTPUT_DISABLE_TYPE_HIGH_IMPEDANCE        /**< high impedance */
#define PCA9685_BASIC_DEFAULT_ALL_CALL_ADDRESS            0xE0                                              /**< 0xE0 */
#define PCA9685_BASIC_DEFAULT_SUBADDRESS_1                0xE2                                              /**< 0xE2 */
#define PCA9685_BASIC_DEFAULT_SUBADDRESS_2                0xE4                                              /**< 0xE4 */
#define PCA9685_BASIC_DEFAULT_SUBADDRESS_3                0xE8                                              /**< 0xE8 */

int pwm_controller_init     (pca9685_address_t addr, uint16_t hz);
int pwm_controller_deinit   (void);
int pwm_controller_write    (pca9685_channel_t channel, float delay_percent, float high_duty_cycle_percent);

#endif
