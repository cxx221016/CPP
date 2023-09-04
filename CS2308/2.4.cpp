#include<vector>
#include<iostream>
#include<numeric>
#include<algorithm>
#include<set>
#include<unordered_map>
#include<queue>
#include<deque>
using namespace std;


int main()
{
    long long int n,m;
    cin>>n>>m;
    //vector<vector<long long int>> edges(m);
    vector<long long int> son(n,0);
    vector<long long int> dp(1<<n,0);
    unordered_map<long long int,long long int> name;
    long long int u=0,v=0;
    long long int sum=0;
    for(long long int i=0;i<m;i++)
    {
        long long int x,y;
        cin>>x>>y;
        /*
        for(u=0;u<sum;u++)
        {
            if(name[u]==x)
                break;
        }
        if(u==sum) name[sum++]=x;
        for(v=0;v<sum;++v)
        {
            if(name[v]==y)
                break;
        }
        if(v==sum) name[sum++]=y;
        son[v]|=(1<<u);
        */
        son[y]|=(1<<x);
    }

    dp[0]=1;

    for(long long int k=0;k<(1<<n);++k)
    {
        if(dp[k]!=0)
        {
            for(long long int i=0;i<n;++i)
            {
                if(((k&son[i])==son[i])&& ((k&(1<<i))==0))
                {
                    dp[k|(1<<i)]+=dp[k];
                }
            }
        }
    }
    
    cout<<dp[(1<<n)-1]<<endl;
    system("pause");
    return 0;

}



