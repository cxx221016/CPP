/*
#include<iostream>
#include<vector>
#include<utility>
#include<sstream>
#include<fstream>
using namespace std;

constexpr int BASEDATEINDEX=0;

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

double Newtonian( vector<pair<double,double>> points,double x)
{
    int n=points.size();
    double y=points[0].second;
    double base=1.0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n-i+1;++j)
        {
            points[j-1].second=(points[j].second-points[j-1].second)/(points[i+j-1].first-points[j-1].first);
        }
        base*=(x-points[i-1].first);
        y+=points[0].second*base;
    }
    return y;
}

int main()
{
    vector<pair<double,double>> lows;
    vector<pair<double,double>> highs;

    fstream ifs("D:\\MY_CODE\\FLTK\\Project 2\\data.txt");
    string line;

    while(getline(ifs,line))
    {
        stringstream is(line);
        string date;
        int high,low;
        is>>date>>high>>low;
        cout<<getindex(date)<<" "<<high<<" "<<low<<endl;
        highs.emplace_back(getindex(date),high);
        lows.emplace_back(getindex(date),low);
    }

    double x;
    while(cin>>x)
    {
        cout<<Newtonian(highs,x)<<" "<<Newtonian(lows,x)<<endl;
    }
    system("pause");
    return 0;
}*/

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;

constexpr int BASEDATEINDEX=0;

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
 
// 函数声明，使得其在被完整定义之前可以被引用
double ChaShang(int n, vector<double>&X, vector<double>&Y);
double Newton(double x, vector<double>&X, vector<double>&Y);
 
int main(){
    // 先将X,Y填充为n个0
    vector<double>X;
    vector<double>Y;
    fstream ifs("D:\\MY_CODE\\FLTK\\Project 2\\data.txt");
    string line;
    int i=0;
    while(getline(ifs,line))
    {
        ++i;
        stringstream is(line);
        string date;
        int high,low;
        is>>date>>high>>low;
        cout<<getindex(date)<<" "<<high<<" "<<low<<endl;
        if(i>=50)
        {X.push_back(getindex(date));
        Y.push_back(high);}
    }
    double x;
    cin>>x;
    cout<<Newton(x,X,Y)<<endl;
    system("pause");
    return 0;
}
 
// 此处为差商的另一种求法，可有差商定义根据数学归纳法求出
double ChaShang(int n,vector<double>&X,vector<double>&Y){
    double f=0;
    double temp=0;
    for(int i=0;i<n+1;i++){
        temp=Y[i];
        for(int j=0;j<n+1;j++){
            if(i!=j){temp /= (X[i]-X[j]);}
        }
        f += temp;
    }return f;
 
}
 
double Newton(double x,vector<double>&X,vector<double>&Y){
    double result=0;
    for(int i=0;i<X.size();i++){
        //此处的temp用于生成牛顿插值多项式里面的多项式乘积因子,(x-1)(x+3)这些
        double temp=1;
        double f=ChaShang(i,X,Y);
        for(int j=0;j<i;j++){
            temp=temp*(x-X[j]);
        }
        // 差商乘以因子得到最终的牛顿插值多项式
        result += f*temp;
    }return result;
}
