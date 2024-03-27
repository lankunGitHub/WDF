#include <mutex>
#include <future>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <atomic>
#include <utility>

#define MAX_SIZE_THREAD 16
#define DEFAULT_SIZE 4

class thread_pool
{
private:
    std::vector<std::jthread> work_thread; // 工作线程
    using TASK = std::function<void()>;
    std::queue<TASK> task_queue;     // 工作列表
    std::atomic<size_t> free_thread; // 空闲线程
    std::atomic<bool> quit_thread;   // 线程运行状态
    std::mutex lock_main_thread;     // 线程锁
    std::mutex lock_work_thread;
    std::mutex lock_try_thread;
    std::condition_variable condition_thread; // 条件变量
    std::stop_token reset_token;

public:
    inline thread_pool() : quit_thread(true), free_thread(16 - DEFAULT_SIZE)
    {
        addthread(DEFAULT_SIZE);
    };
    inline ~thread_pool()
    {
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
        using Ret = std::future<decltype(func(args...))>;
        auto task = std::make_shared<std::packaged_task<Ret>>(
            std::bind(std::forward<F>(func), std::forward<Args>(args)...));
        std::future<Ret> ret_future = task->get_future();
        std::lock_guard<std::mutex> lock_task_queue(lock_main_thread);
        task_queue.emplace((*task)());
        if(free_thread > 0 && task_queue.size() > work_thread.size())
        {
            int j = lock_work_thread.try_lock();
            if(j == -1) addthread(1);
        }
        condition_thread.notify_one();
        return ret_future;
    };
    // 添加线程数量，最大为16（默认为4）
    void addthread(size_t new_size)
    {
        if (new_size == work_thread.size())
            return;
        std::unique_lock<std::mutex> lock_task(lock_main_thread);
        for (; work_thread.size() <= MAX_SIZE_THREAD && new_size > 0; --new_size)
        {
            work_thread.emplace_back([this]()
                                     {
                    while(!reset_token.stop_requested())
                    {
                        std::unique_lock<std::mutex> work_lock(lock_work_thread);
                        while(task_queue.empty())
                        {
                            condition_thread.wait(work_lock);
                        }
                        if(!task_queue.empty())   
                        { 
                            TASK task;
                            task = std::move(task_queue.front());
                            task_queue.pop();
                            work_lock.unlock();
                            task();
                        }
                    } });
            --free_thread;
        }
    };
    void reset_size(size_t new_size = 4)
    {
        std::unique_lock<std::mutex> lock_task(lock_main_thread);
        if (new_size <= MAX_SIZE_THREAD && new_size >= work_thread.size())
            addthread(new_size - work_thread.size());
        else
        {
            free_thread = MAX_SIZE_THREAD - new_size;
            if (lock_work_thread.try_lock())
            {
                for(auto temp = work_thread.begin();free_thread <= 16 && new_size >= 0;++temp,--new_size)
                {
                    reset_token = temp->get_stop_token();
                    temp->request_stop();
                    temp->join();
                }
                condition_thread.notify_all();
            }
        }
    };
    int work_num() {return work_thread.size();};
};

