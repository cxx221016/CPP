#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<string>
#include<functional>
using namespace std;

const double e=2.7182818284590452353602874713527;


double x2(double x)
{
    return x*x;
}

double minus(double x)
{
    return -x;
}

double ex(double x)
{
    return pow(e,x);
}

double y(double x)
{
    return ex(::minus(x2(x)));
}

double Integral(function<double(double)> f,double a,double b,int n)
{
    double h=(b-a)/n;
    double sum=0;
    for(int i=0;i<n;++i)
    {
        sum+=f(a+i*h);
    }
    return sum*h;
}

double Integral2(function<double(double,double)> f,double xa,double xb,double ya,double yb,int n)
{
    double hx=(xb-xa)/n;
    double hy=(yb-ya)/n;
    double sum=0;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            sum+=f(xa+i*hx,ya+j*hy);
        }
    }
    return sum*hx*hy;
}

double Simpson(function<double(double)> f,double a,double b,int n)
{
    double h=(b-a)/n;
    double sum=0;
    for(int i=0;i<n;++i)
    {
        sum+=f(a+i*h)+4*f(a+(i+0.5)*h)+f(a+(i+1)*h);
    }
    return sum*h/6;
}

double Simpson2(function<double(double,double)> f,double xa,double xb,double ya,double yb,int n)
{
    double hx=(xb-xa)/n;
    double hy=(yb-ya)/n;
    double sum=0;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            sum+=f(xa+i*hx,ya+j*hy)+4*f(xa+(i+0.5)*hx,ya+j*hy)+f(xa+(i+1)*hx,ya+j*hy);
        }
    }
    return sum*hx*hy/6;
}

int main()
{
    double a,b;
    int n;
    while(true)
    {
        cin>>a>>b>>n;
        cout<<fixed<<setprecision(6)<<Integral(y,a,b,n)<<endl;
        cout<<fixed<<setprecision(6)<<Simpson(y,a,b,n)<<endl;
    }
    system("pause");
    return 0;
}
