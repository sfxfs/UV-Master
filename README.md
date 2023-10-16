# UV-Master

本项目是适用于水下潜航器的控制程序，适用于 Linux 嵌入式系统，并且具有高可移植性。

***本程序使用到的所有开源项目***：

- [cJSON](https://github.com/DaveGamble/cJSON.git) *用于解析 JSON 格式数据*
- [jsonrpc-c](https://github.com/hmng/jsonrpc-c.git) *tcp 协议的 jsonrpc 服务端*
- [libgpiod](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git) *用于驱动芯片的 gpio 外设*
- [libev](https://github.com/enki/libev.git) *高性能网络事件库*
- [i2c-tools](https://git.kernel.org/pub/scm/utils/i2c-tools/i2c-tools.git) *用于驱动芯片的 i2c 外设*
- [Melon](https://github.com/Water-Melon/Melon.git) *C语言扩展功能库*
- [picohttpparser](https://github.com/h2o/picohttpparser.git) *HTTP 报头解析库*
- [libdriver](https://github.com/hepingood) *外设驱动库*
- [EasyLogger](https://github.com/armink/EasyLogger.git) *内存占用小的日志库*

## 开发

### 软件

- 系统：推荐使用基于 **Linux** 的相关系统（如 **Ubuntu** (推荐20.04) 和 **Manjaro** 等等），如使用 **Windows** 可以在 **WSL** 环境下开发
- IDE：本项目使用 **CMake** 构建系统，推荐使用 *Jetbrain* 出品的 **CLion**，若使用 **VSCode** 请安装 **CMake** 相关插件

### 编译

- 交叉编译请使用对应架构的相关工具链
- 编译本项目前请先安装好相关依赖库（位于3rd）

### 约定

#### 命名

- 变量：形似 `example_val_like`，类型定义 `typedef example_val_t`
- 函数：单词小写以下划线分割，如：`example_fun_like`

#### 注意事项

- 非必要请减少使用全局变量
- 减少使用 `extern` 来使变量对其他文件可访问，不要放在头文件
- 非必要请减少使用无符号变量
- 一般函数最好有返回是否执行成功的 `int` 变量，`0` 为成功， `-1` 为失败
- 请最好不要多于三层嵌套 `for,while,if`
- 不需要在多个文件中调用的函数请加 `static` 前缀
- 创建变量记得赋初值
- 切记多写注释，每个函数也要有符合 Doxygen 规范的注释

## 编译

1. 新建一个构建文件夹并进入：

   ```shell
   mkdir build && cd build
   ```

2. 使用 *cmake* 生成构建文件：

   ```shell
   cmake ..
   ```

3. 使用 *make* 命令进行编译：

   ```shell
   make
   ```
