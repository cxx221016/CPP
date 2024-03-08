#include <iostream>
#include <string>


using namespace std;

class A
{

public:
    int a;
    A(int a) : a(a) {}
};




int main()
{
    const A a(10);
    // a.a = 20; //error
    A &b = const_cast<A &>(a);
    b.a = 20;
    cout << a.a << endl;
    system("pause");
    return 0;
}