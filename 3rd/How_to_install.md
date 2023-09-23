请提前安装依赖包：

```shell
sudo apt-get install -y autoconf automake libtool autoconf-archive m4 pkg-config
```

------

## libev

```shell
$ ./configure --prefix=<安装绝对路径> --host=<交叉编译工具链>

$ make

$ make install
```



## libgpiod

```shell
$ ./autogen.sh --enable-tools=yes --prefix=<安装绝对路径> --host=<交叉编译工具链>

$ make

$ make install
```



## i2c-tools
```shell
$ export CC=arm-cortexa9-linux-gnueabihf-gcc

$ export STRIP=arm-cortexa9-linux-gnueabihf-strip

$ export AR=arm-cortexa9-linux-gnueabihf-ar

# 安装绝对路径 PREFIX 请直接修改根目录 Makefile

$ make

$ make install
```

------

编译产生的文件请都放在 `/usr/` 目录下对应文件夹，工具链请放在 `.../sysroot/usr/` 目录下对应文件夹
