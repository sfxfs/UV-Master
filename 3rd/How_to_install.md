## libev
```shell
./configure --prefix=<安装绝对路径> --host=arm-rockchip830-linux-uclibcgnueabihf

make
make install
```



## libgpiod
```shell
./autogen.sh --enable-tools=yes --prefix=<安装绝对路径> --host=arm-rockchip830-linux-uclibcgnueabihf

# 如果遇到 malloc 相关错误，删除 config.h.in 最后一行

make
make install
```



## i2c-tools
```shell
export CC=arm-rockchip830-linux-uclibcgnueabihf-gcc
export STRIP=arm-rockchip830-linux-uclibcgnueabihf-strip
export AR=arm-rockchip830-linux-uclibcgnueabihf-ar

make
make install
```

------

编译产生的文件请都放在 `/usr/` 目录下对应文件夹，工具链请放在 `/sysroot/usr/` 目录下对应文件夹
