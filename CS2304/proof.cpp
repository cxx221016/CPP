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


using namespace std;

default_random_engine e(time(nullptr));
uniform_int_distribution<int> u(0,25);

int func(int n)
{
    std::deque<char> que;
    while(que.size()<4) que.push_back('a'+u(e));
    //int n=100000000-4;
    int cnt=0;
    int base=n/10;
    while(n--)
    {
        que.push_back('a'+u(e));
        std::string str(que.begin(),que.end());
        if(str=="proof") cnt++;
        if(n%base==0) std::cout<<n<<'\n';
        que.pop_front();
    }
    return cnt;
}


int main()
{
    int threadnums=10;
    //std::vector<packaged_task<int()>> tasks(threadnums);
    std::vector<future<int>> nums(threadnums);
    std::vector<thread> threads(threadnums);
    for(int i=0;i<10;++i)
    {
        packaged_task<int()> task=packaged_task<int()>(std::bind(func,100000000));
        nums[i]=task.get_future();
        threads[i]=thread(std::move(task));
    }
    for(int i=0;i<10;++i)
    {
        threads[i].join();
    }
    vector<int> ress(threadnums);
    for(int i=0;i<10;++i)
    {
        std::cout<<(ress[i]=nums[i].get())<<" ";
    }
    std::cout<<std::endl;
    std::cout<<(double)accumulate(ress.begin(),ress.end(),0)/threadnums<<'\n';
    system("pause");
}