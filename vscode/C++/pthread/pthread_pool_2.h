#include <mutex>
#include <future>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <atomic>
#include <utility>
#include <condition_variable>
#include <iostream>
#include <stop_token>

#define DEFAULT_SIZE 4

class thread_pool
{
private:
    std::vector<std::jthread> work_thread; // 工作线程
    using TASK = std::function<void()>;
    std::queue<TASK> task_queue; // 工作列表
    std::atomic<size_t> max_size_thread;
    std::atomic<size_t> free_thread;          // 空闲线程
    std::atomic<bool> quit_thread;            // 线程运行状态
    std::mutex lock_main_thread;              // 线程锁
    std::condition_variable condition_thread; // 条件变量
    std::stop_source stop_source;

public:
    inline thread_pool() : quit_thread(true), free_thread(16 - DEFAULT_SIZE), max_size_thread(16)
    {
        add_thread(DEFAULT_SIZE);
    };
    inline ~thread_pool()
    {
        stop_source.request_stop();
        condition_thread.notify_all();
        for (auto &temp_thread : work_thread)
        {
            if (temp_thread.joinable())
                temp_thread.join();
        }
    };

public:
    // 传入执行函数和参数
    template <class F, class... Args>
    auto execute(F &&func, Args &&...args) -> std::future<decltype(func(args...))>
    {
        using Ret = decltype(func(args...));
        auto task = std::make_shared<std::packaged_task<Ret()>>(
            std::bind(std::forward<F>(func), std::forward<Args>(args)...));
        std::future<Ret> ret_future = task->get_future();
        {
            std::lock_guard<std::mutex> lock(lock_main_thread);
            task_queue.emplace([task]()
                               { (*task)(); });
        }
        condition_thread.notify_one();
        return ret_future;
    };

    // 添加线程数量，最大为16（默认为4）
    void add_thread(size_t new_size)
    {
        std::unique_lock<std::mutex> lock(lock_main_thread);
        for (; work_thread.size() < max_size_thread && new_size > 0; --new_size)
        {
            work_thread.emplace_back([this, stop_token = stop_source.get_token()]()
                                     {
                                         while (!stop_token.stop_requested() || !task_queue.empty())
                                         {
                                             std::function<void()> task;
                                             {
                                                 std::unique_lock<std::mutex> work_lock(lock_main_thread);
                                                 condition_thread.wait(work_lock, [this, &task_token = stop_token]() {
                                                     return !task_queue.empty() || task_token.stop_requested();
                                                 });
                                                 if (task_queue.empty())
                                                     continue;
                                                 task = std::move(task_queue.front());
                                                 task_queue.pop();
                                             }
                                             task();
                                         } });
            --free_thread;
        }
    }
    // 重置线程数量
    void reset_size(size_t new_size = DEFAULT_SIZE)
    {
        if (new_size == work_thread.size())
            return;
        if (new_size < work_thread.size())
        {
            stop_source.request_stop();
            for (size_t i = new_size; i < work_thread.size(); ++i)
            {
                condition_thread.notify_one();
            }
        }
        else
        {
            add_thread(new_size - work_thread.size());
        }
    }
    // 获得工作线程数
    int work_num() { return work_thread.size(); };
    // 修改最大并发数
    void change_max_thread(size_t new_size)
    {
        if (new_size < work_num())
        {
            reset_size(new_size);
            max_size_thread = new_size;
        }
        else
        {
            max_size_thread = new_size;
        }
    };
};