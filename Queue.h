// Queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>

/**
 * @brief A thread-safe queue supporting a maximum size and blocking/non-blocking pop operations.
 * 
 * @tparam T The type of the elements stored in the queue.
 */
template <typename T>
class Queue {
public:
    // Constructor to initialize the queue with a fixed size.
    Queue(int size) : maxSize(size), front(0), back(0), count(0) {
        buffer = new T[size];
    }

    // Destructor to clean up allocated memory.
    ~Queue() {
        delete[] buffer;
    }

    // Push a new element into the queue. Drops the oldest element if the queue is full.
    void Push(T element) {
        std::unique_lock<std::mutex> lock(mtx);

        if (count == maxSize) {
            // Drop the oldest element
            front = (front + 1) % maxSize;
            --count;
        }

        // Add the new element
        buffer[back] = element;
        back = (back + 1) % maxSize;
        ++count;

        // Notify one waiting thread
        condVar.notify_one();
    }

    // Pop an element from the queue. Blocks indefinitely if the queue is empty.
    T Pop() {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until the queue is not empty
        condVar.wait(lock, [this] { return count > 0; });

        T value = buffer[front];
        front = (front + 1) % maxSize;
        --count;

        return value;
    }

    // Pop an element from the queue with a timeout. Throws an exception if the queue is empty after the timeout.
    T PopWithTimeout(int milliseconds) {
        std::unique_lock<std::mutex> lock(mtx);
        if (!condVar.wait_for(lock, std::chrono::milliseconds(milliseconds), [this] { return count > 0; })) {
            throw std::runtime_error("Timeout: no element available to pop.");
        }

        T value = buffer[front];
        front = (front + 1) % maxSize;
        --count;

        return value;
    }

    // Get the current number of elements in the queue.
    int Count() const {
        std::unique_lock<std::mutex> lock(mtx);
        return count;
    }

    // Get the maximum size of the queue.
    int Size() const {
        return maxSize;
    }

private:
    T* buffer;                    // Dynamic array to store queue elements
    int maxSize;                  // Maximum number of elements the queue can hold
    int front;                    // Index of the front element
    int back;                     // Index of the back element
    int count;                    // Current number of elements in the queue

    mutable std::mutex mtx;       // Mutex for thread-safe access
    std::condition_variable condVar; // Condition variable for blocking operations
};

#endif // QUEUE_H
