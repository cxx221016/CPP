#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;

pair<int,int> getpos(int id,int n)
{
    int r = (id - 1) / n, c = (id - 1) % n;
    if (r % 2 == 1) {
        c = n - 1 - c;
    }
    return {n - 1 - r, c};
}

int snakesAndLadders(vector<int> &board,int dst) {
    int n = board.size();
    vector<int> vis(n);
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (int i = 1; i <= 6; ++i) {
            int nxt = p.first + i;
            if (board[nxt] > 0) { // 存在蛇或梯子
                nxt=board[nxt];
            }
            if (nxt == dst) { // 到达终点
                return p.second + 1;
            }
            if (!vis[nxt]) {
                vis[nxt] = true;
                q.emplace(nxt, p.second + 1); // 扩展新状态
            }
        }
    }
    return -1;
}


int main()
{
    int n;
    cin>>n;
    vector<int> g(n+1,-1);
    int s;
    cin>>s;
    while(s--)
    {
        int x,y;
        cin>>x>>y;
        g[x]=y;
    }
    int t;
    cin>>t;
    while(t--)
    {
        int x,y;
        cin>>x>>y;
        g[x]=y;
    }

    cout<<snakesAndLadders(g,n);
    system("pause");
    return 0;
}