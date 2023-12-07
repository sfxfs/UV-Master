#ifndef UVM_CFG_DEF_H
#define UVM_CFG_DEF_H

#include <stdint.h>
#include <stdbool.h>

/*---- PROPELLER ----*/
enum propeller_pos
{
    PP_FRONT_RIGHT,
    PP_FRONT_LEFT,
    PP_CENTER_RIGHT,
    PP_CENTER_LEFT,
    PP_BACK_RIGHT,
    PP_BACK_LEFT,

    PROPELLER_NUM,
};

struct propeller_attr
{
    bool reversed;
    bool enabled;
    int16_t channel;
    int16_t deadzone_upper;
    int16_t deadzone_lower;
    float power_positive;
    float power_negative;
};

struct propeller_params
{
    int16_t pwm_freq_offset;
    struct propeller_attr attr[PROPELLER_NUM];
};

/*---- DEV_CTL ----*/
enum dev_ctl_em
{
    DEV_CTL_ARM,
    DEV_CTL_LIGHT,

    DEV_NUM,
};

struct dev_ctl_attr
{
    bool enabled;
    int16_t channel;
    uint16_t pMax;
    uint16_t nMax;
    uint16_t reset;
    int16_t step;
};

struct dev_ctl_params
{
    struct dev_ctl_attr attr[DEV_NUM];
};

/*---- ROCKET_RATIO ----*/
enum rocket_axis_em
{
    RA_X,
    RA_Y,
    RA_Z,
    RA_R,

    ROCKET_AXIS_NUM,
};

struct rocket_ratio_attr
{
    bool enabled;
    bool reversed;
    float ratio_p;
    float ratio_n;
};

struct rocket_ratio_params
{
    struct rocket_ratio_attr attr[ROCKET_AXIS_NUM][PROPELLER_NUM];
};

/*---- OTHERS ----*/
struct server_attr
{
    uint16_t port;
    uint16_t timeout;
};

struct others_config_params
{
    struct server_attr server_attr;
};

/*---- CONFIG ----*/
struct config_data
{
    struct propeller_params propeller;
    struct dev_ctl_params dev_ctl;
    struct rocket_ratio_params rocket_ratio;
    struct others_config_params others;
};

#endif
