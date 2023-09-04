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
    vector<bool> iscut(n,false);
    //stack<int> st;
    int timestamp=0;

    function<void(int)> tarjan=[&](int u)
    {
        int childcnt=0;
        dfn[u]=low[u]=timestamp++;
        for(int v:graph[u])
        {
            if(dfn[v]==-1)
            {
                childcnt++;
                parent[v]=u;
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u]&& u!=0)   iscut[u]=true;
            }
            else if(v!=parent[u]) low[u]=min(low[u],dfn[v]);
        }
        if(u==0&&childcnt>1) iscut[u]=true;
    };
    for(int i=0;i<n;i++)
        if(dfn[i]==-1)
            tarjan(i);
    for(int i=0;i<n;i++)
        if(iscut[i])
            cout<<i+1<<endl;
    system("pause");
    return 0;
}

/*
6 6
1 2
2 3
3 5
5 4
4 6
2 4
*/