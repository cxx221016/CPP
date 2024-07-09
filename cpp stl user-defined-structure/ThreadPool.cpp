#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <stdexcept>

class ThreadPool
{
public:
    ThreadPool(size_t threads);
    template <class F, class... Args>
    auto enqueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();

private:
    // 线程池中的工作线程
    std::vector<std::thread> workers;
    // 任务队列
    std::queue<std::function<void()>> tasks;

    // 同步机制
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// 线程池的构造函数，启动指定数量的工作线程
ThreadPool::ThreadPool(size_t threads) : stop(false)
{
    for (size_t i = 0; i < threads; ++i)
    {
        workers.emplace_back([this]
                             {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                    if (this->stop && this->tasks.empty()) {
                        return;
                    }
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            } });
    }
}

// 添加新任务到任务队列中
template <class F, class... Args>
auto ThreadPool::enqueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop)
        {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        tasks.emplace([task]()
                      { (*task)(); });
    }
    condition.notify_one();
    return res;
}

// 线程池的析构函数，停止所有工作线程
ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers)
    {
        worker.join();
    }
}

class thread_pool
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    using func_t = std::function<void()>;
    bool stop;

    std::queue<func_t> tasks;
    std::vector<std::thread> workers;

public:
    thread_pool(size_t thread_num) : stop(false)
    {
        for (int i = 0; i < thread_num; ++i)
        {
            workers.emplace_back([this]
                                 {
                while(true){
                    func_t task;
                    {
                        std::unique_lock<std::mutex> ul(mtx);
                        cv.wait(ul, [this]
                                { return this->stop || !this->tasks.empty(); });
                        if (this->stop)
                        {
                            return;
                        }

                        if (tasks.empty())
                        {
                            continue;
                        }
                        task=tasks.front();
                        tasks.pop();
                    }
                
                    task();

                } });
        }
    }

    ~thread_pool()
    {
        {
            std::unique_lock<std::mutex> ul(mtx);
            this->stop = true;
        }

        std::for_each(workers.begin(), workers.end(), std::mem_fn(std::thread::join));
    }

    template <typename F, typename... Args>
    auto enqueue(F &&f, Args... args) -> std::future<std::result_of_t<F(Args...)>>
    {
        using R = std::result_of_t<F(Args...)>;
        auto task = std::make_shared<std::packaged_task<R()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto result = task->get_future();
        {
            std::unique_lock<std::mutex> ul(mtx);
            if (this->stop)
            {
                throw std::runtime_error("the threadpool has stoped");
            }
            tasks.push([task]
                       { (*task)(); });
        }
        cv.notify_one();
        return result;
    }
};

// 示例任务函数
int exampleTask(int n)
{
    // std::cout << "Processing task: " << n << std::endl;
    printf("Processing task : %d\n", n);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // std::cout << "Task " << n << " done" << std::endl;
    printf("Task : %d done\n", n);
    return n;
}

int main()
{
    thread_pool pool(4); // 创建线程池，包含4个线程

    std::vector<std::future<int>> results;
    for (int i = 0; i < 8; ++i)
    {
        results.emplace_back(pool.enqueue(exampleTask, i));
    }

    for (auto &&result : results)
    {
        printf("[main] result=%d\n", result.get());
    }
    system("pause");
    return 0;
}
