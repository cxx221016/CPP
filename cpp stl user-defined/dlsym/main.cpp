#include<iostream>
#include<tapi.h>
#include<dlcapi.h>
using namespace std;

int test(int a,int b)
{
    return add(a,b);
}

int main()
{
    cout<<"Begin"<<endl;
    cout<<test(1,2)<<endl;
    cout<<"End"<<endl;
    return 0;
}