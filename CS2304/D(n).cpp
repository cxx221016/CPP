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
#define E 2.7182818284590452353602874713527
default_random_engine e(time(nullptr));

bool cp(int n)
{
    vector<int> nums(n);
    iota(nums.begin(),nums.end(),0);
    unordered_set<int> seen(nums.begin(),nums.end());
    for(int i=0;i<n;++i)
    {
        uniform_int_distribution<int> u(0,seen.size()-1);
        int j=u(e);
        auto it=seen.begin();
        advance(it,j);
        if(*it==i) return false;
        seen.erase(it);
    }
    
    return true;
}




int main()
{
    std::cout<<"please input n: ";
    int n;
    cin>>n;
    int m=10000;
    int threadnums=10;
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
    std::cout<<1/E<<'\n';

    system("pause");
    return 0;
}