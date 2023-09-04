#include"Polyfit.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<utility>
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

int main()
{
    vector<double> dates;
    vector<double> lows;
    vector<double> highs;

    fstream ifs("D:\\MY_CODE\\FLTK\\Project 2\\data.txt");
    string line;

    while(getline(ifs,line))
    {
        stringstream is(line);
        string date;
        int high,low;
        is>>date>>high>>low;
        //if(getindex(date)>=0)
        //{
        dates.push_back(getindex(date));
        highs.push_back(high);
        lows.push_back(low);
        cout<<getindex(date)<<" "<<high<<" "<<low<<endl;
        //}
    }
    /*
    double y[] = {7,16,6,18,6,6,10,8};
    double x[] = {-109.71,-101.81,-103.83,-99.89,-90,-112.17,-93.5,-96.13};
    std::vector<double> Mtx(std::begin(x),std::end(x));
    std::vector<double> Mty(std::begin(y),std::end(y));
    
    Polyfit objPolyfit(Mtx,Mty,4);
    vector<double> coefs=objPolyfit.getcoef();
    for(auto& coef:coefs)
    {
        cout<<coef<<" ";
    }
    cout<<endl;
    double in;
    while(cin>>in)
    {
        cout<<objPolyfit.Cal(in)<<endl;
    }*/
    /*
    cout<<"[\n";
    for(int i=0;i<dates.size();++i)
    {
        cout<<dates[i]<<" "<<highs[i]<<'\n';
    }
    cout<<"]";
    */
    
    Polyfit Polyhigh(dates,highs,2);
    Polyfit Polylow(dates,lows,2);
    double in;
    while(cin>>in)
    {
        cout<<"High  "<<Polyhigh.Cal(in)<<" , low  "<<Polylow.Cal(in)<<endl;
    }
    system("pause");
    return 0;
}