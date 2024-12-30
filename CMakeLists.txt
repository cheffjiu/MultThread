cmake_minimum_required(VERSION 3.30) #cmake最低版本要求

project(My_Thread) #项目名称

set(CMAKE_CXX_STANDARD 11) #c++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON) #编译器不满足c++11报错

set(CMAKE_BUILD_TYPE "Debug") #cmake的构建模式 debug 或者 relese

#设置库和可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#添加include和src子目录
add_subdirectory(src)

#添加可执行文件
add_executable(my_project main.cpp)

#链接src生成的库到可执行文件
target_link_libraries(my_project PRIVATE my_thread_library)

#添加include目录到my_project
target_include_directories(my_project PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
