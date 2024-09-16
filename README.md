# UV-Master

English | [简体中文](README_CN.md)

This project is a highly modular and portable underwater robot control program based on embedded systems. It separates logic from hardware using an abstraction layer, is compatible with multiple control platforms, and has been successfully tested on hardware platforms based on Allwinner H3 and WCH CH32V307.

## I. Features

1. Remote control of the robot
2. Algorithms providing directional and depth control
3. Sensor data collection
4. Optional peripherals (lights, manipulator arms, sonar, etc.)
5. Network OTA (Over-The-Air) updates

## II. Project Structure

### Communication Abstraction Layer (CAL)

Currently, only one solution is available, which involves an HTTP server coupled with the JsonRPC protocol.

#### Interfaces

- tcp_server.c

#### Drivers

- rpc_cjson.c

#### Applications

- uvm_cal.c

### Hardware Abstraction Layer (HAL)

The interface part currently includes hardware drivers specific to Linux systems.

#### Interfaces

- interface_xxx.c (contains calls to various utility interface functions)

#### Drivers

- driver_xxx.c

#### Applications

- xxx.c

### Configuration Manager (CFG)

Currently, configuration management is based on the Linux file system.

#### Interfaces

- uvm_cfg_intf.c

#### Drivers

- cfg_xxx.c

#### Applications

- uvm_cfg.c