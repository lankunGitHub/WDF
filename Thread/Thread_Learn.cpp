#include<iostream>
#include<thread>
#include<string>
#include<mutex>
#include<unistd.h>
#include<chrono>
#include<condition_variable>
#include<queue>
#include<vector>
#include<functional>

/*int a = 0;

std::mutex m,m1,m2;
std::timed_mutex mtimes;

std::queue<int> q_queue;
std::condition_variable cond;

void func1(std::string a)
{
    std::cout << a << std::endl;
    return;
}

void func2()
{
    for (int i = 0; i < 10; i++)
    {
        m.lock();
        a += 1;
        m.unlock();
    }
}

void func3()
{
    m1.lock();
    sleep(1);
    m2.lock();
    m1.unlock();
    m2.unlock();
}

void func4()
{
    m2.lock();
    sleep(1);
    m1.lock();
    m2.unlock();
    m1.unlock();
}*/
//int main()
    //std::string s1 = "hello";
    
    /*
    线程创建
    std::thread thread1(func1,s1);
    */


    /*
    是否可以执行join或detach,返回bool类型
    bool able = thread1.joinable();
    */
    
    /*
    等待执行
    thread1.join();
    */
    
    /*
    后台运行子线程
    thread1.detach();
    */

    /*
    互斥量
    thread1(func2);
    thread2(func2);
    join(thread1,thread2);
    */
    /*死锁
    std::thread thread1(func3);
    std::thread thread2(func4);
    thread1.join();
    thread2.join();
    std::cout << "over" << std::endl;
    修改方法，func中获取m1和m2的顺序相同
    */


    /*
    lock_guard模板类(自动构造锁和解锁)
    void func()
    {
        for(int i=0;i<100;i++)
        {
            std::lock_guard<std::mutex> lk(m);
            a++;
        }
    }
    */

    /*
    unique_lock模板类
    void func()
    {
        for(int i=0;i<100;i++)
        {
            std::unique_lock<std::timed_mutex> lk(m,defer_lock);  //加defer_lock需要手动加锁，解锁
            阻塞5秒后就不会阻塞了
            lk.try_lock_for(std::chrono::seconds(5));
            a++;
        }
        
    }
    */


    /*
    call_once只使用一次
    std::call_once(once_flag,args);

    */

    /*
    条件变量
    void Producers()
    {
        for(int i=0;i<10;i++)
        {
            std::unique_lock<std::mutex> lk(m);
            q_queue.push(i);
            q_queue.notify_once();
        }
    }
    void Consumer()
    {
        while(1)
        {
            std::unique_lock<std::mutex> lk(m);
            q_queue.wait(lk,[]() {return q_queue.empty()});
            int value = q_queue.front();
            q_queue.pop();
        }
    }
    */
   // return 0;



/*实现线程池*/
class ThreadPool
{
    ThreadPool(int nThreads) : m_stop(false)
    {
        for (int i = 0; i < nThreads; i++)
        {
            m_thread.emplace_back([this] {
                while(1)
                {
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_cond.wait(lock, [this] {
                        return m_stop ||!m_tasks.empty();
                    });

                    if(!stop && !task_queue.empty())  return;

                    std::function<void()> task(std::move(task_queue.front()));
                    task_queue.pop();
                    task();
                }
            });
            
        }
    }

    ~ThreadPool()
    {
        std::unique_lock<std::mutex> lock(m);
        m_stop = true;

        m_cond.notify_all();
        for(auto &t:m_thread)
        {
            t.join();
        }
    }

    

    private:
    std::vector<std::thread> m_thread;
    std::queue<std::function<void()>> task_queue;

    std::mutex m_mutex;
    std::condition_variable m_cond;

    bool m_stop;
}

//注意，当线程执行时，在未阻塞时，主线程也会继续执行，此时线程某些参数内容的消失，如指针释放等，会造成错误