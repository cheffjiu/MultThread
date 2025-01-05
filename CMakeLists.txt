#项目主CMakeLists.txt

#定义Cmake最低版本
cmake_minimum_required(VERSION 3.30)

# 项目名称
project(MutiThread)

#设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#设置build类型 Debug or Release
set(CMAKE_BUILD_TYPE Debug)

#添加子目录
add_subdirectory(src)

#添加test目录
enable_testing()
add_subdirectory(tests)

#查找已安装的googletest
#find_package(GTest REQUIRED)
