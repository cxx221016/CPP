#include<vector>
#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;

class Solution
{
public:
    vector<vector<int>>dirs{{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
    inline bool isvalid(int i,int j,vector<vector<int>>& chess)
    {
        if(i<0||i>=8||j<0||j>=8||chess[i][j]) return false;
        return true;
    }
    vector<pair<int,int>> findnext(int i,int j,vector<vector<int>>& chess)
    {
        vector<int> w(64,0);
        vector<pair<int,int>> res;
        for(auto& dir:dirs)
        {
            int ni=i+dir[0],nj=j+dir[1];
            if(isvalid(ni,nj,chess))
            {
                res.emplace_back(ni,nj);
                for(auto& dir:dirs)
                {
                    int nni=ni+dir[0],nnj=nj+dir[1];
                    if(isvalid(nni,nnj,chess)) ++w[8*ni+nj];
                }
            }
        }
        sort(res.begin(),res.end(),[&](auto& a,auto& b)
        {
            return w[a.first*8+a.second]<w[b.first*8+b.second];
        });
        return res;
    }
    bool dfs(vector<vector<int>>& chess,int i,int j,int total)
    {
        if(chess[i][j]!=0) return false;
        chess[i][j]=total;
        if(total==64) return true;
        vector<pair<int,int>> getnext=findnext(i,j,chess);
        for(auto& pr:getnext)
        {
            if(dfs(chess,pr.first,pr.second,total+1)) return true;
        }
        chess[i][j]=0;
        return false;
    }

    void display(vector<vector<int>>& chess)
    {
        for(auto& row:chess)
        {
            for(auto& col:row)
            {
                cout.width(2);
                cout.fill('0');
                cout<<col<<" ";
            }
            cout<<endl;
        }
    }
    void Knights_tour_problem()
    {
        vector<vector<int>> chess(8,vector<int>(8,0));
        auto begin=clock();
        dfs(chess,2,0,1);
        auto end=clock();
        auto runTime = (double)(end - begin) / CLOCKS_PER_SEC;
        cout<<runTime<<endl;
        display(chess);
    }
};

int main()
{
    Solution S;
    S.Knights_tour_problem();

    system("pause");
    return 0;
}