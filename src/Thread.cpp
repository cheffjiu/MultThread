#include "Thread.h"
#include <iostream>
#include <thread>
#include <unistd.h>

// Constructor with callable function



//Deconstructor
Thread::~Thread()
{
    if (started&&!joined)
    {
        pthread_detach(thread_id);
    }
}


//Thread join
void Thread::join(){
    if(!started){throw std::runtime_error("Thread is not started");}
    if(joined){throw std::runtime_error("Thread is already joined");}
    pthread_join(thread_id,nullptr);
    joined=true;
}

//Thread detach
void Thread::detach(){
    if(!started){throw std::runtime_error("Thread is not started");}
    if(joined){throw std::runtime_error("Thread is already joined,cannot detach");}
    pthread_detach(thread_id);
    started=false;
}

//Check if thread is joinable
bool Thread::joinable()const{
    return started&&!joined;
}

//Static function for hardware concurrency
 unsigned int Thread::my_hardware_concurrency(){
    return std::thread::hardware_concurrency();
}

//Thread entry function
void* Thread::thread_entry(void* arg){
    auto thread_data = static_cast<ThreadData*>(arg);
    thread_data->func();
    delete thread_data;
    return nullptr;
}
