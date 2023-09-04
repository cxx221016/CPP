#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>
#include<cmath>
using namespace std;

double cross(const pair<double,double>& a, const pair<double,double>& b, const pair<double,double>& c)
{
    return (b.first-a.first)*(c.second-a.second) - (b.second-a.second)*(c.first-a.first);
}


double dis(const pair<double,double>& a, const pair<double,double>& b)
{
    return (b.first-a.first)*(b.first-a.first) + (b.second-a.second)*(b.second-a.second);
}

void Graham(const vector<pair<double,double>>& points,vector<pair<double,double>>& stk)
{
    stk.push_back(points[0]);
    stk.push_back(points[1]);
    for(double i = 2; i < points.size(); i++)
    {
        while(stk.size()>=2 && cross(stk[stk.size()-2], stk[stk.size()-1], points[i])<0)
            stk.pop_back();
        stk.push_back(points[i]);
    }
}

int main()
{
    double n;
    cin >> n;
    vector<pair<double,double>> points(n);
    for(double i = 0; i < n; i++)    cin >> points[i].first >> points[i].second;
    sort(points.begin(), points.end(), [](const pair<double,double>& a,const  pair<double,double>& b)
    {
        return a.second==b.second ? a.first<b.first : a.second<b.second;
    });
    sort(points.begin()+1, points.end(), [&points](const pair<double,double>& a, const pair<double,double>& b)
    {
        double c = cross(points[0], a, b);
        return c==0 ? dis(points[0], a)<dis(points[0], b) : c>0;
    });

    vector<pair<double,double>> stk;
    Graham(points,stk);

    //for(auto& p : stk)    cout << p.first << " " << p.second << endl;
    cout << stk.size() << endl;
    system("pause");
    return 0;
}

/*
9
-4 1
-3 3
-2 2
-1 2
-2 4
0 0
1 4
2 3
2 1
*/