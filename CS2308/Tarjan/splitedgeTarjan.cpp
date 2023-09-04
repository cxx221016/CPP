#include<iostream>
#include<vector>
#include<stack>
#include<functional>
using namespace std;


int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> graph(n);
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> dfn(n,-1);
    vector<int> low(n,-1);
    vector<int> parent(n,-1);
    vector<pair<int,int>> bridge;
    //stack<int> st;
    int timestamp=0;

    function<void(int)> tarjan=[&](int u)
    {
        dfn[u]=low[u]=timestamp++;
        for(int v:graph[u])
        {
            if(dfn[v]==-1)
            {
                parent[v]=u;
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(low[v]>dfn[u])   bridge.emplace_back(u,v);
            }
            else if(v!=parent[u]) low[u]=min(low[u],dfn[v]);
        }
    };
    for(int i=0;i<n;i++)
        if(dfn[i]==-1)
            tarjan(i);
    for(auto p:bridge)
        cout<<p.first+1<<" "<<p.second+1<<endl;
    system("pause");
    return 0;
}

/*
6 6
1 4
1 3 
4 2
3 2
2 5
5 6
*/