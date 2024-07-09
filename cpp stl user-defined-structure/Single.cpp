#include <memory>
#include <mutex>

// template <typename T>
// class Singleton
// {
// private:
//     static std::once_flag flag;
//     static std::shared_ptr<T> ptr;

// public:
//     Singleton() = delete;
//     Singleton(const Singleton &) = delete;
//     Singleton &operator=(const Singleton &) = delete;
//     template <typename... Args>
//     static std::shared_ptr<T> instance(Args... args)
//     {
//         std::call_once(flag, [&]()
//                        { ptr.reset(new T(std::forward<Args>(args)...)) });
//         return ptr;
//     }
// };

// template <typename T>
// std::shared_ptr<T> Singleton<T>::ptr = nullptr;

// template <typename T>
// std::once_flag Singleton<T>::flag;

class SingletonLazy
{
    static SingletonLazy *instance;
    static std::mutex mtx;
    SingletonLazy()
    {
    }

    ~SingletonLazy()
    {
    }

public:
    SingletonLazy(const SingletonLazy &) = delete;
    SingletonLazy(SingletonLazy &&) = delete;

    static SingletonLazy *getInstance()
    {
        if (!instance)
        {
            std::lock_guard<std::mutex> lg(mtx);
            if (!instance)
            {
                instance = new SingletonLazy();
            }
        }
        return instance;
    }
};

SingletonLazy *SingletonLazy::instance = nullptr;
std::mutex SingletonLazy::mtx;

class SingletonEager
{
    static SingletonEager *instance;
    SingletonEager()
    {
    }
    ~SingletonEager()
    {
    }

public:
    SingletonEager(const SingletonEager &) = delete;
    SingletonEager(SingletonEager &&) = delete;

    static SingletonEager *getInstance()
    {
        return instance;
    }
};

SingletonEager *SingletonEager::instance = new SingletonEager();