// main.cpp
#include <iostream>
#include "Queue.h"
#include <thread>
#include <chrono>

void writingThread(Queue<int>& queue) {
    queue.Push(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    queue.Push(2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    queue.Push(3);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    queue.Push(4); // Element 2 is dropped!
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    queue.Push(5);
}

void readingThread(Queue<int>& queue) {
    std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Ensure Push(1) is called
    std::cout << "Pop() -> " << queue.Pop() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Ensure Push(3) is called
    std::cout << "Pop() -> " << queue.Pop() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Ensure Push(4) is called
    std::cout << "Pop() -> " << queue.Pop() << std::endl;

    // Wait for Push(5) to unblock
    std::cout << "Pop() -> " << queue.Pop() << std::endl;
}

int main() {
    Queue<int> queue(2); // Create a queue with size 2

    std::thread writer(writingThread, std::ref(queue));
    std::thread reader(readingThread, std::ref(queue));

    writer.join();
    reader.join();

    return 0;
}

