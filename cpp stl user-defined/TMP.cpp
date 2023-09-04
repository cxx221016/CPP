#include<iostream>
#include<utility>
#include<ctime>

using namespace std;

//sqrt
template<bool FLAG,typename FT,typename ST>
struct ifthenelse{};

template<typename FT,typename ST>
struct ifthenelse<true,FT,ST>
{
    typedef FT type;
};

template<typename FT,typename ST>
struct ifthenelse<false,FT,ST>
{
    typedef ST type;
};


template<int N,int LO=0,int HI=N>
struct Sqrt
{
    static constexpr auto mid=(LO+HI+1)/2;
    typedef typename ifthenelse<(N<mid*mid),Sqrt<N,LO,mid-1>,Sqrt<N,mid,HI>>::type TMP;
    static constexpr auto value=TMP::value;
};

template<int N,int M>
struct Sqrt<N,M,M>
{
    static constexpr auto value=M;
};


/*
template<int N,int LO=0,int HI=N>
struct Sqrt
{
    enum{mid=(LO+HI+1)/2};
    typedef typename ifthenelse<(N<mid*mid),Sqrt<N,LO,mid-1>,Sqrt<N,mid,HI>>::type TMP;
    enum{value=TMP::value};
};

template<int N,int M>
struct Sqrt<N,M,M>
{
    enum{value=M};
};*/

 //n!
template<size_t N>
struct Factory
{
    static const size_t value=N*Factory<N-1>::value;
};

template<>
struct Factory<0>
{
    static const size_t value=1;
};


/*
template<size_t N>
struct Factory
{
    enum{value=N*Factory<N-1>::value};
};

template<>
struct Factory<0>
{
    enum{value=1};
};
*/

int funcFactory(int n)
{
    int res=1;
    while(n)
    {
        res*=n;
        n--;
    }
    return res;
}

int main()
{
    cout<<"n!"<<endl;
    int times=1000000;
    auto TMP_begin=clock();
    while(times--) Factory<100>::value;
    auto TMP_end=clock();
    cout<<(double)(TMP_end-TMP_begin)/CLOCKS_PER_SEC<<'\n';

    cout<<"----------------------------"<<endl;
    times=1000000;
    auto begin=clock();
    while(times--) funcFactory(100);
    auto end=clock();
    cout<<(double)(end-begin)/CLOCKS_PER_SEC<<'\n';

    cout<<Sqrt<110>::value<<endl;
    system("pause");
    return 0;
}
