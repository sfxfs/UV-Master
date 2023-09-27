#ifndef _GPIO_LIBD_H_
#define _GPIO_LIBD_H_

int rov_gpiod_set_input(const char *path, unsigned int offset);
int rov_gpiod_set_output(const char *path, unsigned int offset, int initial_value);

int rov_gpiod_set_value(const char *path, unsigned int offset, int value);
int rov_gpiod_get_value(const char *path, unsigned int offset);

#endif
