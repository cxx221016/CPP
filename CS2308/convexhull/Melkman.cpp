#include <iostream>
#include <vector>
#include <stack>
#include <functional>
#include <algorithm>
#include <cmath>
using namespace std;

double cross(const pair<double, double> &a, const pair<double, double> &b, const pair<double, double> &c)
{
    return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

double dis(const pair<double, double> &a, const pair<double, double> &b)
{
    return (b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second);
}

void Melkman(const vector<pair<double, double>> &points, vector<pair<double, double>> &stk, int &head, int &tail)
{
    int n = points.size();
    stk[tail++] = points[0];
    int i = 0;
    for (; i < n; ++i)
    {
        stk[tail] = points[i];
        if (cross(stk[head], points[i], points[i + 1]))
            break;
    }
    stk[--head] = stk[++tail] = points[++i];
    if (cross(stk[n], stk[n + 1], stk[n + 2]) < 0)
        swap(stk[n], stk[n + 1]);
    for (++i; i < n; ++i)
    {
        if (cross(stk[tail - 1], stk[tail], points[i]) && cross(stk[head + 1], stk[head], points[i]))
        {
            continue;
        }
        while (tail - head > 1 && cross(stk[tail - 1], stk[tail], points[i]) <= 0)
            --tail;
        stk[++tail] = points[i];
        while (tail - head > 1 && cross(stk[head + 1], stk[head], points[i]) <= 0)
            ++head;
        stk[--head] = points[i];
    }
}
int main()
{
    double n;
    cin >> n;
    vector<pair<double, double>> points(n);
    for (double i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;
    sort(points.begin(), points.end(), [](const pair<double, double> &a, const pair<double, double> &b)
         { return a.second == b.second ? a.first < b.first : a.second < b.second; });
    sort(points.begin() + 1, points.end(), [&points](const pair<double, double> &a, const pair<double, double> &b)
         {
        double c = cross(points[0], a, b);
        return c==0 ? dis(points[0], a)<dis(points[0], b) : c>0; });

    vector<pair<double, double>> stk(2 * n);
    int head = n, tail = n;
    Melkman(points, stk, head, tail);
    /*
    stk.push_back(points[0]);
    stk.push_back(points[1]);
    for(double i = 2; i < n; i++)
    {
        while(stk.size()>=2 && cross(stk[stk.size()-2], stk[stk.size()-1], points[i])<=0)
            stk.pop_back();
        stk.push_back(points[i]);
    }
    */
    for (int i = head; i <= tail; i++)
        cout << stk[i].first << " " << stk[i].second << endl;
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