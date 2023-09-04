#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<unordered_set>
#include<unordered_map>
#include<string>
#include<sstream>
#include<cmath>
#include<map>
#include<queue>
#include<ctime>
#include<random>
#include<fstream>
#include<stack>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tmax;
    int n,m,k;
    cin>>n>>m>>k;
    int t,c;
    vector<pair<int,int>> limits;
    while(n--)
    {
        cin>>t>>c;
        limits.emplace_back(t-c-k+1,t-k);
        tmax=max(tmax,t-k);
    }
    vector<int> querys(m);
    for(auto& query:querys) cin>>query;
    vector<int> ress(max(tmax,m)+2,0);
    /*
    for(auto& [be,en]:limits)
    {
        for(int i=0;i<m;++i)
        {
            if(querys[i]>be&&querys[i]<=en)  ress[i]++;
        }
    }*/
    for(auto& limit:limits)
    {
        int be,en;
        tie(be,en)=limit;
        if(en<=0) continue;
        if(be<1) be=1;
        ress[be]++;
        ress[en+1]--;
    }
    for(int i=1;i<=m;++i)
    {
        ress[i]+=ress[i-1];
    }
    for(auto& query:querys)
    {
        cout<<ress[query]<<'\n';
    }
    cout<<flush;
    system("pause");
    return 0;
}