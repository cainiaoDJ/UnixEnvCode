## 本仓库是《Unix环境高级编程》第3版的单例子运行版本

# 使用编译器
CLion

# CMakeLists.txt 范例
```shell
cmake_minimum_required(VERSION 3.15)
project(UnixEnvCode1 C)
include_directories("${pathto}/github/apue.3e/include")
link_libraries("${pathto}/github/apue.3e/lib/libapue.a")
set(CMAKE_C_STANDARD 99)

add_executable(UnixEnvCode1 ${pathOfYouCodeFile})

```

`${}` 里面的内容替换成自己的路径或者文件。
需要先下载随书的源码，编译之后引入`libapue.a` 库。不然在CLion无法编译通过。