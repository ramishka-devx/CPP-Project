#pragma once

#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

class ThreadManager {
public:
    ThreadManager(size_t numThreads = std::thread::hardware_concurrency());
    ~ThreadManager();

    // Disable copying
    ThreadManager(const ThreadManager&) = delete;
    ThreadManager& operator=(const ThreadManager&) = delete;

    // Submit a task to be executed by the thread pool
    void submitTask(std::function<void()> task);

    // Wait for all submitted tasks to complete
    void waitForCompletion();

    // Get the number of worker threads
    size_t getThreadCount() const { return threads.size(); }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    
    void workerThread();
};