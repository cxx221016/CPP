// 训练计划.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<unordered_set>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    scanf("%d %d", &n, &m);
    vector<int> mp(m + 1,0), days(m + 1,0);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &mp[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &days[i]);
    }

    vector<int> former(m + 1,-1), later(m + 1,0);
    bool flag = true;
    for (int i = 1; i <= m; ++i)
    {
        if (mp[i] == 0) former[i] = 1;
        else
        {
            int j = mp[i];
            former[i] = former[j] + days[j];
        }

        if (former[i] + days[i] - 1 > n)
        {
            flag = false;
        }
        cout << former[i];
        if (i <= m - 1) cout << " ";
    }
    cout << endl;

    if (!flag) return 0;
    for (int i = m; i >=1; --i)
    {
        if (later[i]==0) later[i] = n - days[i] + 1;
        if (mp[i]!=0)
        {
            if (later[mp[i]]!=0) later[mp[i]] = min(later[mp[i]], later[i] - days[mp[i]]);
            else later[mp[i]] = later[i] - days[mp[i]];
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        cout << later[i];
        if (i <= m - 1) cout << " ";
    }
    cout << endl;
    return 0;

}