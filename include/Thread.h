#ifndef __Thread_h
#define __Thread_h

#include <pthread.h>  // for pthread
#include <functional> //for std::function
#include <utility>    //for std::forward ,std::move
#include <stdexcept>
#include <atomic>

class Thread
{
private:
    pthread_t thread_id; // posix thread handle
    bool started;        // thread started flag
    bool joined = false; // thread joined flag
    struct ThreadData
    {
        std::function<void()> func;
    };
    static void *thread_entry(void *arg); // thread entry function
public:
    // Constructor and Destructor
    Thread() : thread_id(0), started(false), joined(false) {}
    template <typename Function, typename... Args>
   Thread(Function &&func, Args &&...args)
    {
        auto thread_data = new ThreadData{std::bind(std::forward<Function>(func), std::forward<Args>(args)...)};
        if (pthread_create(&thread_id, nullptr, Thread::thread_entry, thread_data) != 0)
        {
            delete thread_data;
            throw std::runtime_error("Failed to create thread");
        }
    }
    ~Thread();
    // Thread management
    void join();
    void detach();
    bool joinable() const;

    // Getters  获取线程的本地句柄
    pthread_t get_native_handle() const;
    static unsigned int my_hardware_concurrency();
};
// 获取硬件线程支持的最大并发数量

#endif