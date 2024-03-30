#ifndef UVM_CFG_INTF_H
#define UVM_CFG_INTF_H

#define CONFIG_FILE_PATH "./config.json"

void* uvm_intf_read_from_file ();
int uvm_intf_write_to_file (const void* content);

#endif
