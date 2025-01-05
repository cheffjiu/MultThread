
#include <gtest/gtest.h>
#include "my_thread.h" // 包含 Thread 类的头文件
#include <atomic>
using namespace std::chrono_literals;

// 测试创建线程
TEST(ThreadTest, CreateThread) {
    bool thread_started = false;
    Thread t([&]() {
        thread_started = true;
    });

    // 确保线程已启动
    std::this_thread::sleep_for(50ms); // 稍微等待一下
    EXPECT_TRUE(thread_started);
}

// 测试线程的 join 方法
// 测试线程的 join 方法
TEST(ThreadTest, ThreadJoin) {
    bool thread_completed = false;

    Thread t([&]() {
        std::this_thread::sleep_for(50ms); // 模拟长时间的计算
        thread_completed = true;
    });

    t.join();  // 阻塞直到线程完成
    EXPECT_TRUE(thread_completed);  // 确保线程已经完成
}
// 测试线程的 join 异常处理
TEST(ThreadTest, ThreadJoinException) {
    Thread t([]() {});

    // 如果线程还没启动，调用 join 应该抛出异常
    EXPECT_THROW(t.join(), std::runtime_error);

    t.join();  // 第一次 join 应该正常

    // 如果线程已经加入，再次 join 应该抛出异常
    EXPECT_THROW(t.join(), std::runtime_error);
}

// 测试线程的 detach 方法
TEST(ThreadTest, ThreadDetach) {
    bool thread_completed = false;

    Thread t([&]() {
        std::this_thread::sleep_for(50ms); // 模拟长时间的计算
        thread_completed = true;
    });

    t.detach();  // 分离线程
    std::this_thread::sleep_for(100ms);  // 稍微等待一下线程结束

    // 线程应该完成
    EXPECT_TRUE(thread_completed);
}

// 测试线程的 detach 异常处理
TEST(ThreadTest, ThreadDetachException) {
    Thread t([]() {});

    // 如果线程还没启动，调用 detach 应该抛出异常
    EXPECT_THROW(t.detach(), std::runtime_error);

    t.join();  // 第一次 join 应该正常

    // 如果线程已经加入，再次 detach 应该抛出异常
    EXPECT_THROW(t.detach(), std::runtime_error);
}

// 测试线程的 joinable 方法
TEST(ThreadTest, ThreadJoinable) {
    Thread t([]() {});
    
    EXPECT_TRUE(t.joinable());  // 线程已经启动且未加入，应该返回 true
    t.join();
    EXPECT_FALSE(t.joinable());  // 线程已加入，应该返回 false
}

// 测试硬件并发数量
TEST(ThreadTest, HardwareConcurrency) {
    unsigned int concurrency = Thread::my_hardware_concurrency();
    
    // 确保并发数大于0，或者我们至少知道它是一个合理的值
    EXPECT_GT(concurrency, 0);
}


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
