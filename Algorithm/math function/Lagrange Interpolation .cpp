#include<iostream>
#include<vector>
#include<utility>
#include<sstream>
#include<cmath>
#include<fstream>
using namespace std;

constexpr int BASEDATEINDEX=55;

int datehash(const string& date)
{
    int mon=stoi(date.substr(0,2));
    int day=stoi(date.substr(3,2));
    return (mon-9)*30+day;
}

int getindex(const string& date)
{
    return datehash(date)-BASEDATEINDEX;
}

double lagrange(const vector<pair<double,double>>& points,double x)
{
    double y=0;
    for(int i=0;i<points.size();++i)
    {
        double base=points[i].second;
        for(int j=0;j<points.size();++j)
        {
            if(j==i) continue;
            base*=(x-points[j].first)/(points[i].first-points[j].first);
        }
        y+=base;
    }
    return y;
}

/*
long double lagrange(const vector<pair<long double,long double>>& points,long double x)
{
    long double y=0;
    for(int i=0;i<points.size();++i)
    {
        long double base=points[i].second;
        for(int j=0;j<points.size();++j)
        {
            if(j==i) continue;
            base*=(x-points[j].first)/(points[i].first-points[j].first);
        }
        y+=base;
    }
    return y;
}*/

long double f(long double x)
{
    return (long double)3*pow(x,15)-pow(x,12)+4;
}

/*
int main()
{
    int n;
    cin>>n;
    long double  x;
    vector<pair<long double,long double>> pre;
    while(n--)
    {
       cin>>x;
       pre.emplace_back(x,f(x));
       cout<<x<<" "<<f(x)<<endl;
    }
    long double z;
    while(cin>>z)
    {
        cout<<lagrange(pre,z)<<" "<<f(z)<<endl;
    }
}*/


int main()
{
    vector<pair<double,double>> lows;
    vector<pair<double,double>> highs;

    fstream ifs("D:\\MY_CODE\\FLTK\\Project 2\\data.txt");
    string line;
    int idx=0;
    while(getline(ifs,line))
    {
        stringstream is(line);
        string date;
        int high,low;
        is>>date>>high>>low;
        cout<<getindex(date)<<" "<<high<<" "<<low<<endl;
        if(idx++>=BASEDATEINDEX)
        {
            highs.emplace_back(getindex(date),high);
            lows.emplace_back(getindex(date),low);
        }
    }

    double x;
    while(cin>>x)
    {
        cout<<lagrange(highs,x)<<" "<<lagrange(lows,x)<<endl;
    }
    system("pause");
    return 0;
}