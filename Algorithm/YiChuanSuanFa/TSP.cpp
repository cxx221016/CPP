#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

int TSP(vector<vector<int>>&graph,int location)
{
    int n=graph.size()-1;
    vector<vector<int>> D(n+1,vector<int>((1<<n),INT_MAX));
    vector<vector<int>> Rec(n+1,vector<int>((1<<n),-1));
    for(int i=1;i<n+1;++i)
    {
        D[i][0]=graph[i][location];
    }

    for(int j=1;j<(1<<n);++j)
    {
        for(int i=1;i<=n;++i)
        {
            int min=INT_MAX;
            if((1<<(i-1))&j==0)
            {
                int length=INT_MAX;
                for(int k=1;k<=n;++k)
                {
                    if((1<<(k-1))&j)
                    {
                        length=graph[i][k]+D[k][j-(1<<(k-1))];
                        if(length<min)
                        {
                            min=length;
                            D[i][j]=min;
                            Rec[i][j]=k;
                        }
                    }
                }
            }
        }
    }
    return D[location][(1<<n)-1-(1<<(location-1))];
}

int main()
{
    int n;
    cin>>n;
    vector<vector<int>> graph(n+1,vector<int>(n+1));
    for(int i=1;i<n+1;++i)
    {
        for(int j=1;j<n+1;++j)
        {
            cin>>graph[i][j];
        }
    }
    int location;
    cin>>location;
    TSP(graph,location);
    return 0;
}