#ifndef MY_THREAD_H
#define MY_THREAD_H
#include "pub_include.h"

class Thread
{
private:
    pthread_t thread_id; // thread ID
    bool started;        // thread started flag
    bool joined = false; // thread joined flag
    struct ThreadData
    {
        std::function<void()> func;
    }; // 线程数据结构，用于存储要在线程中执行的函数和参数
    static void *thread_entry(void *arg); // 线程入口函数，用于执行绑定到线程的函数
public:
    // Constructor and Destructors

    /**
     * @brief 线程类的构造函数
     *
     * 初始化线程类的成员变量：
     * - thread_id：线程ID，初始化为0
     * - started：线程是否已启动的标志，初始化为false
     * - joined：线程是否已连接的标志，初始化为false
     */
    Thread() : thread_id(0), started(false), joined(false) {}

    template <typename Function, typename... Args> // 模板构造函数，用于创建线程并绑定函数和参数
    /**
     * @brief 构造函数，用于创建线程
     *
     * 该构造函数接受一个可调用对象func和一组参数args，
     * 并将它们绑定到线程执行的函数中。
     *
     * @param func 要在线程中执行的函数或可调用对象
     * @param args 传递给func的参数包
     * @throw std::runtime_error 如果线程创建失败，则抛出此异常
     */
    Thread(Function &&func, Args &&...args)
    {
        // 创建一个新的 ThreadData 对象，并将传入的函数和参数绑定
        auto thread_data = new ThreadData{std::bind(std::forward<Function>(func), std::forward<Args>(args)...)};

        // 尝试创建一个新的线程
        if (pthread_create(&thread_id, nullptr, Thread::thread_entry, thread_data) != 0)
        {
            // 如果线程创建失败，则删除之前创建的 ThreadData 对象
            delete thread_data;

            // 抛出运行时错误，表示线程创建失败
            throw std::runtime_error("Failed to create thread");
        }
        started = true;
        joined = false;
    }

    ~Thread();

    void join();
    void detach();
    bool joinable() const;

    // Getters  获取线程的本地句柄
    pthread_t get_native_handle() const;
    // 获取硬件线程支持的最大并发数量
    static unsigned int my_hardware_concurrency();
};

#endif