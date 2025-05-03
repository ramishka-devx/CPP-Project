#include "../include/ThreadManager.h"
#include <stdexcept>
#include <iostream>

ThreadManager::ThreadManager(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(&ThreadManager::workerThread, this);
    }
}

ThreadManager::~ThreadManager() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void ThreadManager::submitTask(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (stop) {
            throw std::runtime_error("ThreadManager is stopping");
        }
        taskQueue.push(std::move(task));
    }
    condition.notify_one();
}

void ThreadManager::waitForCompletion() {
    std::unique_lock<std::mutex> lock(queueMutex);
    condition.wait(lock, [this]() { return taskQueue.empty(); });
}

void ThreadManager::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this]() { 
                return stop || !taskQueue.empty(); 
            });
            
            if (stop && taskQueue.empty()) {
                return;
            }
            
            task = std::move(taskQueue.front());
            taskQueue.pop();
        }
        
        try {
            task();
        } catch (const std::exception& e) {
            std::cerr << "Exception in worker thread: " << e.what() << std::endl;
        }
    }
}

void ThreadManager::start() {
}

void ThreadManager::stop() {
}

void ThreadManager::addTask(std::function<void()> task) {
}

bool ThreadManager::isRunning() const {
    return false;
}

size_t ThreadManager::getNumThreads() const {
    return numThreads;
}

void ThreadManager::setNumThreads(size_t newNumThreads) {
}

size_t ThreadManager::getTaskCount() const {
    return taskQueue.size();
}

size_t ThreadManager::getActiveThreadCount() const {
    return activeThreads;
}

void ThreadManager::processNextTask() {
} 