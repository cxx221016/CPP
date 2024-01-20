#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

long long int mod(long long int x,long long int y)
{
    long long int coef=trunc(x/y);
    cout<<x<<"-"<<"("<<coef<<")"<<"*"<<y<<"="<<x-coef*y<<endl;
    return x-coef*y;
}

int main()
{
    mod(2013,81);
    mod(-2013,81);
    mod(pow(10,7),143);
    cout<<__gcd(-413,2013)<<endl;
    cout<<__gcd(37,1590)<<endl;
    cout<<(int(pow(5,11)) % 23)<<endl;
    cout<<(int(pow(5,9)) % 26)<<endl;
    system("pause");
}