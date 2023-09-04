#include<iostream>
#include<random>
#include<ctime>
using namespace std;


/*
vector<unsigned> get_v()
{
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0,9);
    vector<unsigned> v;
    for(size_t i=0;i<10;++i)
    {
        v.push_back(u(e));
    }
    return v;
}

vector<int> static_get_v()
{
    static default_random_engine e;
    static uniform_int_distribution<int> u(-2,1);
    vector<int> v;
    for(size_t i=0;i<10;++i)
    {
        v.push_back(u(e));
        cout<<u(e)<<endl;
    }
    return v;
}*/





int main()
{
    /*
    vector<unsigned> v1(get_v());
    vector<unsigned> v2(get_v());
    cout<<(v1==v2)<<endl;
    vector<int> v3(static_get_v());
    vector<int> v4(static_get_v());
    cout<<(v3==v4)<<endl;
    //引擎初始化
    default_random_engine r1,r2(2147483646),r3,r4(32767);
    r3.seed(32767);
    for(size_t i=0;i<100;++i)
    {
        if(r1()==r2()) cout<<"unseed "<<i<<endl;
        if(r3()!=r4()) cout<<"seed   "<<i<<endl;
    }
    
    default_random_engine r(time(nullptr));
    uniform_real_distribution<double> rl;  //随机实数
    normal_distribution<> n(4,1.5) ;       //非均匀 平均值 4  标准差 1.5
    bernoulli_distribution b;             //默认0.5

    for(size_t i=0;i<10;++i)
    {
        cout<<rl(r)<<endl;
        cout<<n(r)<<endl;
    }*/
    constexpr int sum=10;
    static default_random_engine e;
    static uniform_int_distribution<int> u(0,1);
	vector<vector<int>> matrix=vector<vector<int>>(sum,vector<int>(sum,0));
    for(auto& level:matrix)
    {
        for(auto& l:level)
        {
            cout<<l<<" ";
        }
        cout<<endl;
    }
    system("pause");
    return 0;

}