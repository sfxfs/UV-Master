#ifndef _GPIO_LIBD_H_
#define _GPIO_LIBD_H_

#include <gpiod.h>

struct gpiod_line_request *gpio_set_output_mode(const char *chip_path, unsigned int offset, enum gpiod_line_value value, const char *consumer);
struct gpiod_line_request *gpio_set_input_mode(const char *chip_path, unsigned int offset, const char *consumer);

#define gpio_set_output_value(request,offset,value) gpiod_line_request_set_value(request,offset,value)
#define gpio_get_input_value(request,offset) gpiod_line_request_get_value(request,offset)
#define gpio_deinit(request) gpiod_line_request_release(request)

#endif
