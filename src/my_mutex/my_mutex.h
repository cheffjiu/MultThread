#ifndef MY_MUTEX_H
#define MY_MUTEX_H

#include "pub_include.h"

class Mutex
{
private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    Mutex() = default;
    ~Mutex() = default;

    Mutex(const Mutex &) = delete;
    Mutex &operator=(const Mutex &) = delete;

    Mutex(Mutex &&) = delete;
    Mutex &operator=(Mutex &&) = delete;

    void lock();
    void unlock();
    bool try_lock();
};

#endif