# ROV-Master

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

   