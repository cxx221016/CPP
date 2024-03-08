#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <regex>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include<complex>
#include <cxxabi.h>
#include <typeinfo>

using namespace std;


class MyClass
{
    public:
    MyClass()
    {
        cout<<"MyClass()"<<endl;
    }
    MyClass(const MyClass& other)
    {
        cout<<"MyClass(const MyClass& other)"<<endl;
    }
    MyClass(MyClass&& other)
    {
        cout<<"MyClass(MyClass&& other)"<<endl;
    }
    ~MyClass()
    {
        cout<<"~MyClass()"<<endl;
    }
};

MyClass* GetTemporary()
{
    MyClass A{};
    return &A;
}



//-fno-elide-constructors

int main()
{
    auto A=GetTemporary();
    return 0;
}

