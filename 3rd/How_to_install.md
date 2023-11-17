> *注意以下教程适用于 armhf 架构的开发板，其他架构请自行修改命令即可*

请提前安装好 [Armhf Linux 编译工具链](https://releases.linaro.org/components/toolchain/binaries/7.5-2019.12/arm-linux-gnueabihf/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz) 并添加到环境变量

请提前安装依赖包：

```shell
sudo apt-get install -y cmake ninja-build autoconf automake libtool autoconf-archive m4 pkg-config
```

------

## libonion

```shell
$ export CC=arm-linux-gnueabihf-gcc

$ export AR=arm-linux-gnueabihf-ar

# 请修改 CMakeLists.txt 来取消编译不需要的模块，以及设置安装路径

$ cmake ...

$ sudo make install
```



## libgpiod

注意！请使用 **v1.6.x** 分支，最新版将无法在较老内核下使用

```shell
$ ./autogen.sh --enable-tools=yes --prefix=<安装绝对路径> --host=arm-linux-gnueabihf

$ make

$ make install
```



## i2c-tools
```shell
$ export CC=arm-linux-gnueabihf-gcc

$ export STRIP=arm-linux-gnueabihf-strip

$ export AR=arm-linux-gnueabihf-ar

# !!! 安装绝对路径 PREFIX 请直接修改根目录 Makefile !!!

$ make

$ make install
```

------

编译产生的文件请都放在 `/usr/` 目录下对应文件夹，工具链请放在 `.../usr/` 相关目录下对应文件夹
