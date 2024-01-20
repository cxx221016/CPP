#include<memory>
#include<mutex>

template<typename T>
class Singleton
{
private:
    static std::once_flag flag;
    static std::shared_ptr<T> ptr;
public:
    Singleton()=delete;
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
    template<typename... Args>
    static std::shared_ptr<T> instance(Args... args)
    {
        std::call_once(flag,[&](){ptr.reset(new T(std::forward<Args>(args)...))});
        return ptr;
    }


};

template<typename T>
std::shared_ptr<T> Singleton<T>::ptr=nullptr;

template<typename T>
std::once_flag Singleton<T>::flag;