// Queue.h

#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>

/**
 * @brief A thread-safe queue that supports a maximum size and blocking/non-blocking pop operations.
 * 
 * @tparam T The type of elements stored in the queue.
 */
template <typename T>
class Queue {
public:
    /**
     * @brief Constructs a queue with a specified maximum size.
     * 
     * @param size The maximum number of elements the queue can hold.
     */
    explicit Queue(int size);

    /**
     * @brief Destroys the queue and frees allocated memory.
     */
    ~Queue();

    /**
     * @brief Pushes an element to the queue. If the queue is full, the oldest element is dropped.
     * 
     * @param element The element to be added to the queue.
     */
    void Push(const T& element);

    /**
     * @brief Pops an element from the queue. Blocks indefinitely if the queue is empty.
     * 
     * @return T The element removed from the front of the queue.
     */
    T Pop();

    /**
     * @brief Pops an element from the queue with a timeout. Throws an exception if the timeout expires.
     * 
     * @param milliseconds The timeout duration in milliseconds.
     * @return T The element removed from the front of the queue.
     * @throws std::runtime_error If the queue is empty after the timeout.
     */
    T PopWithTimeout(int milliseconds);

    /**
     * @brief Returns the current number of elements in the queue.
     * 
     * @return int The number of elements currently stored in the queue.
     */
    int Count() const;

    /**
     * @brief Returns the maximum size of the queue.
     * 
     * @return int The maximum number of elements the queue can hold.
     */
    int Size() const;

private:
    T* buffer;                      ///< Dynamic array to store queue elements.
    int maxSize;                    ///< Maximum number of elements the queue can hold.
    int front;                      ///< Index of the front element.
    int back;                       ///< Index of the back element.
    int count;                      ///< Current number of elements in the queue.

    mutable std::mutex mtx;         ///< Mutex for thread-safe access.
    std::condition_variable condVar; ///< Condition variable for blocking operations.
};

#include "Queue.hpp" // Include the implementation file

#endif // QUEUE_H

