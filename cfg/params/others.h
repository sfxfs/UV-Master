#ifndef UVM_CFG_OTHERS_H
#define UVM_CFG_OTHERS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint16_t port;
    uint16_t timeout;
} server_attr;

typedef struct
{
    server_attr server_config;
} others_params;

others_params *others_create_with_init_val (void);
void *others_s2j (others_params *params);
others_params *others_j2s (void *json);

#endif
