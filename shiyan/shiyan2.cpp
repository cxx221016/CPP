#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>
#include <set>
#include <type_traits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <optional>
#include <thread>
// #include"json.hpp"
using namespace std;
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

class A
{

public :
template <typename T>
void change(const T &args, int CPU=0, int Memory=0, int Disk=0, int Network=0, int GPU=0)
{
    std::cout << "args" << args << " ";
    std::cout << "CPU:" << CPU << " ";
    std::cout << "Memory:" << Memory << " ";
    std::cout << "Disk:" << Disk << " ";
    std::cout << "Network:" << Network << " ";
    std::cout << "GPU:" << GPU << " ";
    std::cout << std::endl;
}
};

class Matrix
{
public:
    template<typename T>
    vector<vector<T>> mul(const vector<vector<T>>& a,const vector<vector<T>>& b)
    {
        int m=a.size(),n=a[0].size(),p=b[0].size();
        vector<vector<T>> res(m,vector<T>(p,0));
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<p;++j)
            {
                for(int k=0;k<n;++k)
                {
                    res[i][j]=(res[i][j]+a[i][k]*b[k][j])%1000000007;
                }
            }
        }
        return res;
    }

    template<typename T>
    vector<vector<T>> pow(vector<vector<T>>& a,int n)
    {
        int m=a.size();
        vector<vector<T>> res(m,vector<T>(m,0));
        for(int i=0;i<m;++i)
        {
            res[i][i]=1;
        }
        while(n)
        {
            if(n&1) res=mul(res,a);
            a=mul(a,a);
            n>>=1;
        }
        return res;
    }
};

enum class girls
{
    xiaoli,
    xiaohong,
    xiaofang
};

template< size_t N>
class girlfriend
{
public:
    girls g;
    girlfriend()
    {
        g=static_cast<girls>(N);
    }
};

template<girls girl>
class Girlfriend
{
public:
    inline static  constexpr  girls g=girl;
};

template<typename T>
class CXX
{
public:
    T t;
    CXX(T t):t(t){}
    void print()
    {
        cout<<t<<endl;
    }
};

class Solution {
public:
    string customSortString(const string& order,const  string& s) 
    {
        int idx=0;
        unordered_map<char,int> mp;
        for(auto& c:order)
        {
            mp[c]=idx++;
        }
        std::string tmp;
        deque<int> dq;
        for(int i=0;i<s.size();++i)
        {
            if(mp.count(s[i]))
            {
                tmp.push_back(s[i]);
                dq.push_back(i);
            }
        }

        sort(tmp.begin(),tmp.end(),[&](const char& a,const char& b)
        {
            return mp[a]<mp[b];
        });
        string res=s;
        for(int i=0;i<dq.size();++i)
        {
            res[dq[i]]=tmp[i];
        }
        return res;
    }
};


int main()
{
    
    system("pause");
    return 0;
}
