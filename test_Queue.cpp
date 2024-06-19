// test_Queue.cpp
#include <gtest/gtest.h>
#include "Queue.h"
#include <thread>
#include <stdexcept>

/**
 * @brief Test the initial state of the queue.
 */
TEST(QueueTest, InitialState) {
    Queue<int> q(3);
    EXPECT_EQ(q.Count(), 0);
    EXPECT_EQ(q.Size(), 3);
}

/**
 * @brief Test pushing elements into the queue.
 */
TEST(QueueTest, Push) {
    Queue<int> q(3);
    q.Push(1);
    q.Push(2);
    q.Push(3);

    EXPECT_EQ(q.Count(), 3);
    q.Push(4); // Should drop the oldest element (1)
    EXPECT_EQ(q.Count(), 3);
}

/**
 * @brief Test popping elements from the queue.
 */
TEST(QueueTest, Pop) {
    Queue<int> q(3);
    q.Push(1);
    q.Push(2);

    EXPECT_EQ(q.Pop(), 1);
    EXPECT_EQ(q.Pop(), 2);
}

/**
 * @brief Test the PopWithTimeout method.
 */
TEST(QueueTest, PopWithTimeout) {
    Queue<int> q(3);

    std::thread writer([&q] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        q.Push(1);
    });

    EXPECT_EQ(q.PopWithTimeout(200), 1);

    writer.join();
}

/**
 * @brief Test that PopWithTimeout throws an exception when the timeout expires.
 */
TEST(QueueTest, PopWithTimeoutThrows) {
    Queue<int> q(3);
    EXPECT_THROW(q.PopWithTimeout(100), std::runtime_error);
}

/**
 * @brief Test thread safety by pushing and popping in different threads.
 */
TEST(QueueTest, ThreadSafety) {
    Queue<int> q(3);

    std::thread writer([&q] {
        for (int i = 0; i < 5; ++i) {
            q.Push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });

    std::thread reader([&q] {
        for (int i = 0; i < 5; ++i) {
            EXPECT_NO_THROW(q.PopWithTimeout(100));
        }
    });

    writer.join();
    reader.join();
}

