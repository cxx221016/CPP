#include<iostream>
#include<vector>
#include<utility>
#include<functional>
#include<iomanip>
using namespace std;

double f(double x)
{
    return 2*x*x*x-4*x*x+3*x-6;
}

double Solve(double x1,double x2,const function<double(double)>&f)
{
    if(f(x1)*f(x2)>0)
    {
        cout<<"cannot use dichotomy"<<endl;
        return 0;
    }

    while(abs(x1-x2)>1e-6)
    {
        double mid=(x1+x2)/2;
        double fleft=f(x1);
        double fmid=f(mid);
        if(fmid==0) break;
        else if(fleft*fmid>0) x1=mid;
        else x2=mid;
    }

    cout<<fixed<<setprecision(6)<<(x1+x2)/2<<endl;
    return (x1+x2)/2;
}

int main()
{
    double x1,x2;
    cin>>x1>>x2;
    Solve(x1,x2,f);
    system("pause");
    return 0;
}