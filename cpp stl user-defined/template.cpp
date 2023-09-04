#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class A
{
    T a;
public:
    A()=default;
    template<typename F>
    class  SY
    {
    public:
        typedef F other;
    };
};

template<typename T,typename F>
using type =typename A<T>::template SY<F>::other;
/*A<T>::template*/

int main()
{
    A<int> tmp;
    type<string,int> a;
    cout<<boolalpha<<is_same_v<type<string,int>,int><<endl;
    system("pause");
}