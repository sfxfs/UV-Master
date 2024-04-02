#include "pwm.h"

#include "pca9685.h"
#include <stdlib.h>

#define us2percent(us) (((us)*100.0)/20000.0) // 一个周期 20 ms (50hz)

void term_pwm_print_help()
{
    printf( "pwm help info:\n"
            "duty {channal:0~15} {us:500~2500}\n"
            "freq {cal_hz:50}\n"
            "reinit {cal_hz:50}\n");
}

// duty / freq / reinit
void term_pwm_handle(const char *args[], int num_args)
{
    if (num_args == 0)
    {
        term_pwm_print_help();
        return;
    }

    // 请务必使用 strncmp，否则有可能导致段错误
    if (strncmp(args[0], "duty", 4) == 0 && num_args >= 3) // duty {channal} {us}
    {
        pca9685_basic_write(atoi(args[1]), 0.0f, us2percent(atoi(args[2])));
    }
    else if (strncmp(args[0], "freq", 4) == 0 && num_args >= 2) // freq {hz}
    {
    }
    else if (strncmp(args[0], "reinit", 6) == 0 && num_args >= 2) // reinit {hz}
    {
        if (pca9685_basic_deinit() == 0)
            pca9685_basic_init(PCA9685_ADDRESS_A000000, atoi(args[1]));
        else
            printf("pca9685 deinit failed...\n");
    }
    else
    {
        printf("pwm command format error\n");
        term_pwm_print_help();
    }
}
