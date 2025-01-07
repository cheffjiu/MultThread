#src/my_thread/CMakeLists.txt

#定义一个lib_my_thread库
add_library(lib_my_thread STATIC my_thread.cpp)

#定义库的输出位置
set_target_properties(lib_my_thread PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/lib
    )

#设置lib_my_thread的头文件
target_include_directories(lib_my_thread PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}              # my_thread 目录
    ${CMAKE_SOURCE_DIR}/include              # 项目的 include 目录
    )
