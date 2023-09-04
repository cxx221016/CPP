#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<stack>
#include<map>
#include<algorithm>
using namespace std;



long long int dfs(long long int now,vector<long long int>& dp,vector<vector<int>>& g,vector<int>& in,int id)
{
    if(dp[now]) return dp[now];
    dp[now]=0;
    for(int i=0;i<id;++i)
    {
        if(in[i]==0&&(now&(1<<i)))
        {
            for(int j=0;j<id;++j)
            {
                if(g[i][j])
                {
                    in[j]--;
                }
            }
            dp[now]+=dfs((now-(1<<i)),dp,g,in,id);
            for(int j=0;j<id;++j)
            {
                if(g[i][j])
                {
                    in[j]++;
                }
            }
        }
    }
    return dp[now];
}

int main()
{
    int n,m;
    cin>>n>>m;
    vector<long long int> dp(1<<n,0);
    vector<vector<int>> g(n,vector<int>(n,0));
    vector<int> in(n,0);
    //map<int,int> mp;
    //int id=0;
    while(m--)
    {
        int x,y;
        cin>>x>>y;
        g[x][y]=1;
        in[y]++;
    }

    for(int i=0;(1<<i)<n;++i) dp[i]=1;
    //cout<<id<<n<<endl;
    cout<<dfs((1<<n)-1,dp,g,in,n)<<endl;
    system("pause");
    return 0;
}