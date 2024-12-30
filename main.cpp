#include "Thread.h"
#include <iostream>

void print_message(const std::string& message, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << message << " (" << i + 1 << ")" << std::endl;
    }
}

int main() {
    try {
        Thread t1(print_message, "Hello from thread 1", 3);
        std::function<void()> bound_func=[]{
            std::cout << "Hello from thread 2!" << std::endl;
        };
        Thread t2(bound_func);
        t1.join();
        t2.detach();

        std::cout << "Main thread completed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
