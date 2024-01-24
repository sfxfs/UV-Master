#include <uvm_cfg.h>

config_data uvm_config;

int main(int argc, char **argv)
{
    uvm_config = uvm_cfg_init();
    return 0;
}
