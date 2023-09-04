#pragma
#include <unordered_map>
#include<map>
#include <functional>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include<chrono>
#include<iomanip>
#include<optional>
#include<thread>


template <typename F, typename... Args>
void Invoke(double delaytime, F &&f, Args &&...args)
{
    std::function<void()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    std::thread tmp([=]()
                    {
                        std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(delaytime)));
                        func(); 
                    });
    tmp.detach();
}
