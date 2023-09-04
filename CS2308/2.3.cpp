#include<vector>
#include<iostream>
#include<numeric>
#include<algorithm>
#include<set>
#include<unordered_map>
#include<queue>
#include<deque>
#include<climits>
using namespace std;


int Bellman_Ford(int src,int dst,int m,int n,const vector<vector<int>>& edges)
{
    vector<vector<int>> dist(m+1,vector<int>(n,0x3f3f3f3f));
    //for_each(dist[0].begin(),dist[0].end(),[](int & v){v=0;});
    dist[0][src]=0;
    for(int i=1;i<=m;i++)
    {
        vector<int> cnt(n,0);
        for(auto& edge:edges)
        {
            int u=edge[0],v=edge[1],w=edge[2];
            if(dist[i][v]<dist[i-1][u]+w)
            {
                if(cnt[v]==0) dist[i][v]=0x3f3f3f3f;
            }
            else 
            {
                dist[i][v]=dist[i-1][u]+w;
                cnt[v]++;
            }
        }
    }
    //cout<<pre[dst]<<endl;
    return dist[m][dst];
}


int main()
{
    int n,e;
    cin>>n>>e;
    vector<vector<int>> edges;
    for(int i=0;i<e;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        edges.push_back({x,y,w});
    }

    int src,dst,m;
    cin>>src>>dst>>m;
    int res=Bellman_Ford(src,dst,m,n,edges);
    if(res>=0x3f3f3f3f) cout<<INT_MAX;
    else cout<<res;
    system("pause");
    return 0;
}



