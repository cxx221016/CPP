#include<iostream>
#include<vector>
#include<utility>
#include<functional>
#include<iomanip>
#include<cmath>
#include<exception>
using namespace std;

double f(double x)
{
    return x*exp(x)-1;
}

double g(double x)
{
    return (x+1)*exp(x);
}

double nextx(double x,const function<double(double)>&f,const function<double(double)>&g)  //求切线与X轴的交点。得到新的x点。
{
	return  x-f(x)/g(x);
}

double Solve(double x,const function<double(double)>&f)
{
    double nx=nextx(x,f,g);
    if(f(nx)<1e-7) {cout<<fixed<<setprecision(6)<<nx<<endl; return nx;}
    else return Solve(nx,f);

    throw runtime_error("No Solution");
}

int main()
{
    double x;
    cin>>x;
    Solve(x,f);
    system("pause");
    return 0;
}