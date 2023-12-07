# UV-Master

本项目是适用于水下潜航器的控制程序，适用于嵌入式系统，并且具有高可移植性。

## 一、文件结构

```shell
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── cal	# 通信抽象层
│   ├── uvm-cal.c
│   └── uvm-cal.h # 供主控制程序调用的 API
├── cfg # 配置管理系统
│   └── cfg-file-tpl # 示例配置文件模板
│       └── config.json
├── exlibs # 第三方库
├── hal # 硬件抽象层
│   ├── app # 驱动应用
│   ├── drv	# 驱动 API
│   ├── intf # 驱动底层接口
│   ├── uvm-hal.c
│   └── uvm-hal.h # 供主控制程序调用的 API
└── src # 主控制程序源代码
    ├── CMakeLists.txt
    ├── ctrl # 控制部分
    ├── dev # 外设部分
    ├── log # 日志系统
    └── rpc # 远程调用的函数
```

在移植本程序或更换硬件方案时只需要修改 `src` 之外的代码即可。