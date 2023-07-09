#!/bin/bash
#需要root权限来运行这个脚本
#该脚本用于安装依赖库，安装系统后只需执行一次

install_path=$(cd `dirname $0`; pwd)
cd $install_path

echo "======================安装WiringNP========================"
cd WiringNP || exit
chmod 777 build
./build
cd ..

echo "======================安装easylogger======================"
cd easylogger || exit
cmake .
make
cp lib/libeasylogger.so /usr/lib/
cp inc/elog.h /usr/include/
cd ..

echo "======================编译libev==========================="
cd libev || exit
chmod 777 ./configure
./configure -prefix=/usr
make
make install

ldconfig

echo "\033[35m=======================构建完成=======================\033[0m" 
exit 0
