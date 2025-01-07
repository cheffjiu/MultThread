#src/my_mutex/CMakeLists.txt

#定义lib_my_mutex库
add_library(lib_my_mutex my_mutex.cpp)

#设置lib_my_mutex库的输出路径
set_target_properties(lib_my_mutex PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/lib)

#链接库需要的头文件
target_link_directories(lib_my_mutex PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    )

