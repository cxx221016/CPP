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
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> dfn(n,-1);
    vector<int> low(n,-1);
    vector<int> parent(n,-1);
    vector<vector<int>> bcc;
    stack<int> st;
    int timestamp=0;

    //边连通分量
    function<void(int)> tarjan=[&](int u)
    {
        dfn[u]=low[u]=timestamp++;
        st.push(u);
        bool flag=false;
        for(int v:graph[u])
        {
            if(dfn[v]==-1)
            {
                parent[v]=u;
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }
            else if(v!=parent[u]||flag) low[u]=min(low[u],dfn[v]);
            else flag=true;
        }
        if(low[u]==dfn[u])
        {
            bcc.push_back({});
            while(true)
            {
                int x=st.top();
                st.pop();
                bcc.back().push_back(x);
                if(x==u)
                    break;
            }
        }
    };
    for(int i=0;i<n;i++)
        if(dfn[i]==-1)
            tarjan(i);
    for(auto& v:bcc)
    {
        for(int i:v)
            cout<<i<<" ";
        cout<<endl;
    }
    system("pause");
    return 0;
}

/*
9 11
0 1
0 3
0 4
0 5
1 2
2 3
3 4
5 6
5 7
5 8
7 8
*/