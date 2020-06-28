## 本仓库是《Unix环境高级编程》第3版的单例子运行版本

# 使用编译器
CLion

# CMakeLists.txt 范例
```sh
cmake_minimum_required(VERSION 3.15)
project(UnixEnvCode1 C)
include_directories("{pathto}/github/apue.3e/include")
link_libraries("{pathto}/github/apue.3e/lib/libapue.a")
set(CMAKE_C_STANDARD 99)

add_executable(UnixEnvCode1 ${pathOfYouCodeFile})

```

`${}` 里面的内容替换成自己的路径或者文件。
需要先下载随书的源码，编译之后引入`libapue.a` 库。不然在CLion无法编译通过。

# 使用gcc编译办法
 ## 设置环境变量
```sh
export UNIX_ENV_CODE="{your source code path}"/apue.3e
# C
export C_INCLUDE_PATH=$UNIX_ENV_CODE/include:$C_INCLUDE_PATH
# CPP
export CPLUS_INCLUDE_PATH=$UNIX_ENV_CODE/include:$CPLUS_INCLUDE_PATH

# 动态链接库搜索路径：
export LD_LIBRARY_PATH=$UNIX_ENV_CODE/lib:$LD_LIBRARY_PATH
# 静态链接库搜索路径：
export LIBRARY_PATH=$UNIX_ENV_CODE/lib:$LIBRARY_PATH
```

 ## 编译步骤
 centos 安装gcc，libbsd
 ```sh
wget http://elrepo.reloumirrors.net/testing/el6/x86_64/RPMS/libbsd-0.4.2-1.el6.elrepo.x86_64.rpm
wget http://elrepo.reloumirrors.net/testing/el6/x86_64/RPMS/libbsd-devel-0.4.2-1.el6.elrepo.x86_64.rpm
rpm -ivh libbsd-0.4.2-1.el6.elrepo.x86_64.rpm
rpm -ivh libbsd-devel-0.4.2-1.el6.elrepo.x86_64.rpm
 ```
安装后执行make all

 ```sh
 gcc test.c -lapue
 ```