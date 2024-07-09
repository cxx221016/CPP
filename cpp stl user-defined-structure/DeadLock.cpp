#include <mutex>
#include <thread>
#include <iostream>

std::mutex mtx1, mtx2;

void func1()
{
    std::lock_guard<std::mutex> lg1(mtx1);

    std::cout << "func1 get mtx1" << std::endl;

    // op
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::lock_guard<std::mutex> lg2(mtx2);

    std::cout << "func1 get mtx2" << std::endl;
}

void func2()
{
    std::lock_guard<std::mutex> lg2(mtx2);

    std::cout << "func2 get mtx2" << std::endl;

    // op
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::lock_guard<std::mutex> lg1(mtx1);

    std::cout << "func2 get mtx1" << std::endl;
}

int main()
{
    std::thread t1(func1), t2(func2);
    t1.join();
    t2.join();
    return 0;
}
