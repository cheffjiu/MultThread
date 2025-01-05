
#include "my_thread.h"
// 析构函数
Thread::~Thread() {
    // 如果线程已启动且尚未加入
    if (started && !joined) {
        // 将线程从进程中分离
        pthread_detach(thread_id);
    }
}

// Thread join
void Thread::join() {
    // 如果线程没有启动，则抛出运行时错误
    if (!started) {
        throw std::runtime_error("Thread is not started");
    }
    // 如果线程已经加入，则抛出运行时错误
    if (joined) {
        throw std::runtime_error("Thread is already joined");
    }
    // 等待线程结束
    pthread_join(thread_id, nullptr);
    // 标记线程已加入
    joined = true;
}

// Thread detach
void Thread::detach() {
    // 如果线程没有启动，则抛出运行时错误
    if (!started) {
        throw std::runtime_error("Thread is not started");
    }

    // 如果线程已经加入，则抛出运行时错误
    if (joined) {
        throw std::runtime_error("Thread is already joined, cannot detach");
    }

    // 分离线程
    pthread_detach(thread_id);
    // 将线程启动状态设置为 false
    joined = true;
}

// 判断线程是否可连接
bool Thread::joinable() const {
    // 判断线程是否已启动且未加入
    return started && !joined;
}

// 获取硬件并发数
unsigned int Thread::my_hardware_concurrency() {
    // 返回当前硬件的并发能力
    return std::thread::hardware_concurrency();
}

// 线程入口函数
void* Thread::thread_entry(void* arg) {
    // 将传入的参数转换为 ThreadData 类型的指针
    auto thread_data = static_cast<ThreadData*>(arg);

    // 调用 ThreadData 对象中定义的函数
    thread_data->func();

    // 删除 ThreadData 对象，释放内存
    delete thread_data;

    // 返回空指针
    return nullptr;
}