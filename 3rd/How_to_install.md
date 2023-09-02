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
$ export CC=<交叉编译工具链>-gcc

$ export STRIP=<交叉编译工具链>-strip

$ export AR=<交叉编译工具链>-ar

$ export PREFIX=<安装绝对路径>
# 或者直接修改根目录 Makefile

$ make

$ make install
```

------

编译产生的文件请都放在 `/usr/` 目录下对应文件夹，工具链请放在 `.../sysroot/usr/` 目录下对应文件夹
