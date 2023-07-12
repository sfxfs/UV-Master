# ROV-Master

## 开发

### 软件

- 系统：推荐 **Ubuntu LTS** 并安装好 `cmake`，**Win** 下请提前安装好 **MinGW**
- IDE：本项目使用 **CMake** 构建系统，推荐使用 *Jetbrain* 出品的 **CLion**，若使用 **VSCode** 请安装 **CMake** 相关插件

### 约定

#### 命名

- 变量：形似 `example_val_like`，类型定义 `typedef example_val_t`
- 函数：单词小写以下划线分割，如：`example_fun_like`

#### 注意事项

- 非必要请减少使用全局变量
- 不要使用 `extern` 来使变量对其他文件可访问
- 非必要请减少使用无符号变量
- 一般函数最好有返回是否执行成功的 `int` 变量，`0` 为成功， `-1` 为失败
- 请最好不要多于三层嵌套 `for,while,if`
- 不需要在多个文件中调用的函数请加 `static` 前缀

## 首次安装

1. 进入 *3rd* 目录：

   ```shell
   cd 3rd
   ```

   

2. 给予 *install.sh* **777** 权限：

   ```shell
   sudo chmod 777 install.sh
   ```

3. 以根用户权限执行 *install.sh*：

   ```shell
   sudo ./install.sh
   ```

   

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

   