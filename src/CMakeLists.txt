#设置源文件和头文件
set(SOURCES Thread.cpp)
#set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../include/Thread.h)

#定义一个静态库或动态库
add_library(my_thread_library SHARED ${SOURCES})

#添加include目录到库文件
target_include_directories(my_thread_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
