#include<vector>
#include<iostream>
#include<numeric>
#include<algorithm>
#include<set>
#include<unordered_map>
#include<queue>
using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<int> nums(n);
    unordered_map<int,int> cnt;
    unordered_map<int,int> idx;
    for(int i=0;i<n;++i)
    {
        cin>>nums[i];
        if(!idx.count(nums[i])) idx[nums[i]]=i;
        cnt[nums[i]]++;
    }

    auto cmp=[&](const int& a,const int& b)
    {
        return cnt[a]==cnt[b]? idx[a]>idx[b]:cnt[a]<cnt[b];
    };

    priority_queue<int,vector<int>,decltype(cmp)> que(cmp);
    for(auto& num:nums)
    {
        que.push(num);
    }

    while(!que.empty())
    {
        cout<<que.top()<<" ";
        que.pop();
    }
    
    
    system("pause");
    return 0;
}