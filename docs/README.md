项目名称：
    基于 POSIX 的线程类库

项目目标：
    实现一个类 Thread，使用 POSIX 标准提供的 pthread 库，提供类似于 C++ 标准库 std::thread 的多线程功能。

应用场景：
    1、企业级应用需要跨平台多线程支持。

    2、替代 C++ 标准库中 std::thread，实现更灵活的线程管理功能。

    3、适用于嵌入式系统、定制系统或资源受限环境

功能需求：

    必备功能
        线程创建
            支持传递函数、Lambda 表达式作为线程任务。
            提供统一接口进行线程管理。

        线程同步

            提供 join 方法阻塞主线程，等待子线程完成。
            提供 detach 方法分离线程，允许线程在后台运行。

        线程状态查询
            提供 joinable 方法检查线程是否可加入。
            提供线程 ID 查询功能。

        硬件支持信息
            提供静态方法 hardware_concurrency 查询硬件支持的最大线程数。

        异常处理
            对线程创建失败或非法操作抛出异常。

    可选功能
        支持线程优先级设置。
        支持线程栈大小配置。


UML 类图
+-------------------+
|     my::thread   |
+-------------------+
| - id: thread::id  |
| - handle: native_handle_type |
+-------------------+
| + thread()                            |
| + thread(Function&&, Args&&...)       |
| + ~thread()                           |
| + join(): void                        |
| + detach(): void                      |
| + joinable(): bool                    |
| + get_id(): thread::id                |
| + native_handle(): native_handle_type |
| + hardware_concurrency(): unsigned int (static) |
+-------------------+


项目结构：
    project/
    |-- include/
    |   |-- Thread.h
    |-- src/
    |   |-- Thread.cpp
    |-- main.cpp
    |-- CMakeLists.txt