#define LOG_TAG "device.pwm_controller"

#include "../interface/pca9685_interface.h"
#include "pwm_controller.h"

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

static pca9685_handle_t gs_handle;        /**< pca9685 handle */

/**
 * @brief     basic example init
 * @param[in] addr is the iic device address
 * @param[in] hz is the output frequency
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
int pwm_controller_init(pca9685_address_t addr, uint16_t hz)
{
    uint8_t res;
    uint8_t reg;
    
    /* link interface function */
    DRIVER_PCA9685_LINK_INIT(&gs_handle, pca9685_handle_t);
    DRIVER_PCA9685_LINK_IIC_INIT(&gs_handle, pca9685_interface_iic_init);
    DRIVER_PCA9685_LINK_IIC_DEINIT(&gs_handle, pca9685_interface_iic_deinit);
    DRIVER_PCA9685_LINK_IIC_READ(&gs_handle, pca9685_interface_iic_read);
    DRIVER_PCA9685_LINK_IIC_WEITE(&gs_handle, pca9685_interface_iic_write);
    DRIVER_PCA9685_LINK_OE_GPIO_INIT(&gs_handle, pca9685_interface_oe_init);
    DRIVER_PCA9685_LINK_OE_GPIO_DEINIT(&gs_handle, pca9685_interface_oe_deinit);
    DRIVER_PCA9685_LINK_OE_GPIO_WRITE(&gs_handle, pca9685_interface_oe_write);
    DRIVER_PCA9685_LINK_DELAY_MS(&gs_handle, pca9685_interface_delay_ms);
    DRIVER_PCA9685_LINK_DEBUG_PRINT(&gs_handle, pca9685_interface_debug_print);
    
    /* set addr pin */
    res = pca9685_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set addr pin failed.\n");
        
        return -1;
    }
    
    /* pca9685 init */
    res = pca9685_init(&gs_handle);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: init failed.\n");
        
        return -1;
    }
    
    /* inactive */
    res = pca9685_set_active(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set active failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set sleep mode */
    res = pca9685_set_sleep_mode(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sleep mode failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set frequency */
    res = pca9685_output_frequency_convert_to_register(&gs_handle, PCA9685_OSCILLATOR_INTERNAL_FREQUENCY, hz, (uint8_t *)&reg);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: output frequency convert to register failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set pre scale */
    res = pca9685_set_prescaler(&gs_handle, reg);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set pre scale failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* disable external clock pin */
    res = pca9685_set_external_clock_pin(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set external clock pin failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* enable auto increment */
    res = pca9685_set_register_auto_increment(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set register auto increment failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set respond sub address 1 */
    res = pca9685_set_respond_subaddress_1(&gs_handle, PCA9685_BASIC_DEFAULT_RESPOND_SUBADDRESS_1);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 1 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set respond sub address 2 */
    res = pca9685_set_respond_subaddress_2(&gs_handle, PCA9685_BASIC_DEFAULT_RESPOND_SUBADDRESS_2);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 2 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set respond sub address 3 */
    res = pca9685_set_respond_subaddress_3(&gs_handle, PCA9685_BASIC_DEFAULT_RESPOND_SUBADDRESS_2);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond sub address 3 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set respond all call */
    res = pca9685_set_respond_all_call(&gs_handle, PCA9685_BASIC_DEFAULT_RESPOND_ALL_CALL);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set respond all call failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set output invert */
    res = pca9685_set_output_invert(&gs_handle, PCA9685_BASIC_DEFAULT_OUTPUT_INVERT);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output invert failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* stop output change */
    res = pca9685_set_output_change(&gs_handle, PCA9685_BASIC_DEFAULT_OUTPUT_CHANGE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output change failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set output driver */
    res = pca9685_set_output_driver(&gs_handle, PCA9685_BASIC_DEFAULT_OUTPUT_DRIVER);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output driver failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set output disable type */
    res = pca9685_set_output_disable_type(&gs_handle, PCA9685_OUTPUT_DISABLE_TYPE_HIGH_IMPEDANCE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set output disable type failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set sub address 1 */
    res = pca9685_set_subaddress_1(&gs_handle, PCA9685_BASIC_DEFAULT_SUBADDRESS_1);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sub address 1 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set sub address 2 */
    res = pca9685_set_subaddress_2(&gs_handle, PCA9685_BASIC_DEFAULT_SUBADDRESS_2);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sub address 2 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set sub address 3 */
    res = pca9685_set_subaddress_3(&gs_handle, PCA9685_BASIC_DEFAULT_SUBADDRESS_3);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sub address 3 failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set all call address */
    res = pca9685_set_all_call_address(&gs_handle, PCA9685_BASIC_DEFAULT_ALL_CALL_ADDRESS);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set all call address failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set sleep mode */
    res = pca9685_set_sleep_mode(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set sleep mode failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* active */
    res = pca9685_set_active(&gs_handle, PCA9685_BOOL_TRUE);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set active failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }

    return 0;
}

int pwm_controller_set_freq (uint16_t hz)
{
    uint8_t res;
    uint8_t reg;
    res = pca9685_output_frequency_convert_to_register(&gs_handle, PCA9685_OSCILLATOR_INTERNAL_FREQUENCY, hz, (uint8_t *)&reg);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: output frequency convert to register failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }
    
    /* set pre scale */
    res = pca9685_set_prescaler(&gs_handle, reg);
    if (res != 0)
    {
        pca9685_interface_debug_print("pca9685: set pre scale failed.\n");
        (void)pca9685_deinit(&gs_handle);
        
        return -1;
    }

    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
int pwm_controller_deinit(void)
{
    uint8_t res;
    
    /* inactive */
    res = pca9685_set_active(&gs_handle, PCA9685_BOOL_FALSE);
    if (res != 0)
    {
        return -1;
    }
    
    /* deinit */
    res = pca9685_deinit(&gs_handle);
    if (res != 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     basic example write
 * @param[in] channel is the pwm channel
 * @param[in] delay_percent is the start delay percent
 * @param[in] high_duty_cycle_percent is the pwm high duty cycle percent
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      0.0 <= delay_percent + high_duty_cycle_percent <= 100.0
 *            0.0 <= delay_percent <= 100.0
 *            0.0 <= high_duty_cycle_percent <= 100.0
 */
int pwm_controller_write(pca9685_channel_t channel, float delay_percent, float high_duty_cycle_percent)
{
    uint8_t res;
    uint16_t on_count, off_count;
    
    /* convert data */
    res = pca9685_pwm_convert_to_register(&gs_handle, delay_percent, high_duty_cycle_percent, (uint16_t *)&on_count, (uint16_t *)&off_count);
    if (res != 0)
    {
        return -1;
    }
    
    /* write channel */
    res = pca9685_write_channel(&gs_handle, channel, on_count, off_count);
    if (res != 0)
    {
        return -1;
    }
    
    return 0;
}
