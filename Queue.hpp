// Queue.hpp

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Queue.h"

template <typename T>
Queue<T>::Queue(int size)
    : maxSize(size), front(0), back(0), count(0) {
    if (size <= 0) {
        throw std::invalid_argument("Size must be positive.");
    }
    buffer = new T[size];
}

template <typename T>
Queue<T>::~Queue() {
    delete[] buffer;
}

template <typename T>
void Queue<T>::Push(const T& element) {
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

template <typename T>
T Queue<T>::Pop() {
    std::unique_lock<std::mutex> lock(mtx);

    // Wait until the queue is not empty
    condVar.wait(lock, [this] { return count > 0; });

    T value = buffer[front];
    front = (front + 1) % maxSize;
    --count;

    return value;
}

template <typename T>
T Queue<T>::PopWithTimeout(int milliseconds) {
    std::unique_lock<std::mutex> lock(mtx);
    
    if (!condVar.wait_for(lock, std::chrono::milliseconds(milliseconds), [this] { return count > 0; })) {
        throw std::runtime_error("Timeout: no element available to pop.");
    }

    T value = buffer[front];
    front = (front + 1) % maxSize;
    --count;

    return value;
}

template <typename T>
int Queue<T>::Count() const {
    std::unique_lock<std::mutex> lock(mtx);
    return count;
}

template <typename T>
int Queue<T>::Size() const {
    return maxSize;
}

#endif // QUEUE_HPP
