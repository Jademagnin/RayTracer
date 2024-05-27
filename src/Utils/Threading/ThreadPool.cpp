/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t numThreads)
    : _stop(false)
{
    _workers.reserve(numThreads);
    for (size_t i = 0; i < numThreads; i++) {
        _workers.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->_queueMutex);
                    this->_condition.wait(lock,
                        [this] {
                            return this->_stop || !this->_tasks.empty();
                        }
                    );
                    if (this->_stop && this->_tasks.empty()) {
                        return;
                    }
                    task = std::move(this->_tasks.front());
                    this->_tasks.pop_front();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(this->_queueMutex);
        this->_stop = true;
    }
    this->_condition.notify_all();
    for (std::thread &worker : this->_workers) {
        worker.join();
    }
}
