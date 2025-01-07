#include"my_mutex.h"

/**
 * @brief 对互斥锁进行加锁操作
 *
 * 使用自旋锁机制对互斥锁进行加锁操作。
 *
 * 如果当前互斥锁已被其他线程占用，则当前线程会不断循环并调用std::this_thread::yield()函数让出CPU时间片，
 * 直到互斥锁被释放并成功获取锁。
 */
void Mutex::lock(){
    // 尝试获取锁
    while(flag.test_and_set(std::memory_order_acquire)){
        // 如果无法获取锁，则放弃当前线程的时间片，让出CPU给其他线程
        std::this_thread::yield();
    }
}

/**
 * @brief 解锁互斥锁
 *
 * 此函数用于解锁互斥锁，允许其他线程进入临界区。
 *
 * 使用std::memory_order_release内存顺序来确保在解锁操作之前的所有内存写入操作对其他线程可见。
 */
void Mutex::unlock(){
    // 清除互斥锁的标志位，并设置内存顺序为发布（release）顺序
    flag.clear(std::memory_order_release);
}

/**
 * @brief 尝试获取互斥锁
 *
 * 尝试获取互斥锁，如果互斥锁当前未被锁定，则成功获取锁并返回 true；
 * 如果互斥锁已被锁定，则不阻塞并立即返回 false。
 *
 * @return 如果成功获取锁则返回 true，否则返回 false。
 */
bool Mutex::try_lock(){
    // 尝试以无阻塞的方式获取锁
    return !flag.test_and_set(std::memory_order_acquire); // 尝试设置标志位，如果设置成功（即标志位之前为0），则返回true，表示成功获取锁；否则返回false
}