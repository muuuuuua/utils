#ifndef YT_SERVER_FACE_FEATURE_THREAD_POOL_H
#define YT_SERVER_FACE_FEATURE_THREAD_POOL_H

#include <functional>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <vector>
#include <queue>
#include <future>


namespace youtu {

class ThreadPool {
public:
    ThreadPool(size_t size) : stopped(false) {
        for (int i = 0; i < size; ++i) {
            pool.emplace_back(
                    [this] {
                        while (!stopped.load()) {
                            task_type task;
                            {
                                std::unique_lock<std::mutex> lock(this->m_lock);
                                this->cv_task.wait(lock, [this] {
                                    return this->stopped.load() || !this->tasks.empty();
                                });
                                if (this->stopped.load())
                                    return;
                                task = std::move(this->tasks.front());
                                this->tasks.pop();
                            }
                            task();
                        }
                    }
            );
        }
    }

    ~ThreadPool() {
        stopped.store(true);
        cv_task.notify_all();
        for (std::thread &thread : pool) {
            if (thread.joinable())
                thread.join();
        }
    }

    template<class F, class... Args>
    auto commit(F &&f, Args &&... args) -> std::future<decltype(f(args...))> {

        using return_type = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        std::future<return_type> future = task->get_future();
        {
            std::lock_guard<std::mutex> lock(m_lock);
            if (stopped.load())
                throw std::runtime_error("thread pool has stopped");
            tasks.emplace([task]() { (*task)(); });
        }
        cv_task.notify_one();

        return future;
    }

private:
    using task_type = std::function<void()>;
    std::vector<std::thread> pool;
    std::queue<task_type> tasks;
    std::mutex m_lock;
    std::condition_variable cv_task;
    std::atomic<bool> stopped;
};
}

#endif //YT_SERVER_FACE_FEATURE_THREAD_POOL_H
