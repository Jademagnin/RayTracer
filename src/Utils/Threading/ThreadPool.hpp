/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ThreadPool
*/

#pragma once

#include <deque>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <optional>
#include <functional>

/**
 * @brief A class that manages a pool of threads for executing tasks.
 */
class ThreadPool {
    public:
        /**
         * @brief Constructs a new ThreadPool.
         * 
         * @param numThreads The number of threads in the pool.
         */
        ThreadPool(size_t numThreads);

        /**
         * @brief Destroys the ThreadPool, ensuring all threads finish execution.
         */
        ~ThreadPool();

        /**
         * @brief Adds a new task to the pool to be executed by a thread.
         * 
         * @tparam F The type of the task function.
         * @param f The task function.
         */
        template<class F>
        void enqueue(F&& f) {
            {
                std::unique_lock<std::mutex> lock(_queueMutex);
                _tasks.emplace_back(std::forward<F>(f));
            }
            _condition.notify_one();
        }

    protected:
    private:
        std::vector<std::thread> _workers; ///< The worker threads.
        std::deque<std::function<void()>> _tasks; ///< The tasks to be executed.
        std::mutex _queueMutex; ///< Mutex for synchronizing access to the task queue.
        std::condition_variable _condition; ///< Condition variable for thread synchronization.
        bool _stop; ///< Flag indicating whether the thread pool is stopping.
};
