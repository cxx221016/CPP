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

void Dijkstra(vector<vector<int>>& edges,int n,int start)
{
    vector<int> dist(n,INT_MAX);
    dist[start]=0;
    set<pair<int,int>> s;
    s.insert({0,start});
    while(!s.empty())
    {
        auto [d,u]=*s.begin();
        s.erase(s.begin());
        for(auto& edge:edges)
        {
            if(edge[0]==u)
            {
                int v=edge[1],w=edge[2];
                if(dist[v]>dist[u]+w)
                {
                    s.erase({dist[v],v});
                    dist[v]=dist[u]+w;
                    s.insert({dist[v],v});
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(dist[i]!=INT_MAX&&i!=start) cout<<i<<" "<<dist[i]<<"\n";
    }
    //cout<<endl;
}

int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> edges;
    for(int i=0;i<m;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        edges.push_back({x,y,w});
    }
    int start;
    cin>>start;
    Dijkstra(edges,n,start);
    system("pause");
    return 0;
}

