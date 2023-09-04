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
    }
    vector<int> dfn(n,-1);
    vector<int> low(n,-1);
    vector<int> parent(n,-1);
    stack<int> st;
    vector<bool> instack(n,false);
    vector<vector<int>> bcc;
    int timestamp=0;

    //边连通分量
    function<void(int)> tarjan=[&](int u)
    {
        st.push(u);
        instack[u]=true;
        dfn[u]=low[u]=timestamp++;
        for(int v:graph[u])
        {
            if(dfn[v]==-1)
            {
                parent[v]=u;
                tarjan(v);
                low[u]=min(low[u],low[v]);
                //if(low[v]>=dfn[u]&& u!=0)   iscut[u]=true;
            }
            else if(instack[v]) low[u]=min(low[u],dfn[v]);
        }
        if(low[u]==dfn[u])
        {
            vector<int> tmp;
            while(st.top()!=u)
            {
                tmp.push_back(st.top());
                instack[st.top()]=false;
                st.pop();
            }
            tmp.push_back(st.top());
            instack[st.top()]=false;
            st.pop();
            bcc.push_back(tmp);
        }
    };
    for(int i=0;i<n;i++)
        if(dfn[i]==-1)
            tarjan(i);

    for(auto& tmp:bcc)
    {
        for(auto& i:tmp)
            cout<<i+1<<" ";
        cout<<endl;
    }
    system("pause");
    return 0;
}

/*
6 7
1 3
3 4
4 5
5 4
3 2
2 1
6 2
*/