#include<atomic>
#include<thread>
#include<mutex>
#include<ctime>
#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<functional>
#include<deque>
#include<random>
#include<future>
#include<thread>
#include<unordered_set>

using namespace std;

bool cp(int  n)
{
    static default_random_engine e(time(nullptr));
    static uniform_real_distribution<double> u(0,n);
    auto  x=u(e);
    return x<(double)1.0/n;
}

int main()
{
    std::cout<<"please input n: ";
    int n;
    cin>>n;
    int threadnums=10;
    int m=n*(n-1)*threadnums/2;
    std::vector<thread> threads(threadnums);
    std::vector<future<int>> nums(threadnums);
    for(int i=0;i<threadnums;++i)
    {
        packaged_task<int()> task=packaged_task<int()>([&]()
        {
            int res=0;
            int times=m/threadnums;
            while(times--)
            {
                res+=cp(n);
            }
            return res;
        });
        nums[i]=task.get_future();
        threads[i]=thread(std::move(task));
    }
    vector<int> ress(threadnums);
    for(int i=0;i<10;++i)
    {
        std::cout<<(ress[i]=nums[i].get())<<" ";
    }
    std::cout<<std::endl;
    std::cout<<(double)accumulate(ress.begin(),ress.end(),0)/m<<'\n';

    system("pause");
    return 0;
}