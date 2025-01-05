#src/CMakeLists.txt

#设置子目录
add_subdirectory(my_thread)

#添加main.cpp的可执行文件
add_executable(main_executable main.cpp)

#设置可执行文件的输出目录
set_target_properties(main_executable PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/bin)

#将lib_my_thread库链接到main_executable
target_link_libraries(main_executable lib_my_thread)

#设置包含库的头文件
target_include_directories(main_executable PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/my_thread    # my_thread 目录
    ${CMAKE_SOURCE_DIR}/include              # 项目的 include 目录
)
