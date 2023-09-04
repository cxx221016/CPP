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

class UnionFind {
public:
    vector<int> parent;
    vector<int> size;
    int n;
    // 当前连通分量数目
    int setCount;
    
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int findset(int x) {
        return parent[x] == x ? x : parent[x] = findset(parent[x]);
    }
    
    bool unite(int x, int y) {
        x = findset(x);
        y = findset(y);
        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    
    bool connected(int x, int y) {
        x = findset(x);
        y = findset(y);
        return x == y;
    }
};


void Kruskal(vector<vector<int>>& edges,int n)
{
    UnionFind u(n);
    sort(edges.begin(),edges.end(),[](vector<int>& a,vector<int>& b)
    {
        return a[2]<b[2];
    });
    int res=0;
    for(auto& edge:edges)
    {
        int x=edge[0],y=edge[1],w=edge[2];
        if(!u.connected(x,y))
        {
            u.unite(x,y);
            //cout<<x<<" "<<y<<" "<<w<<endl;
            res+=w;
        }
    }
    cout<<res<<endl;
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
    Kruskal(edges,n);
    system("pause");
    return 0;
}

