#include<vector>
#include<iostream>
#include<numeric>
#include<algorithm>
#include<set>
#include<unordered_map>
using namespace std;

int main()
{
    int n;
    cin>>n;
    unordered_map<int,int> idx;
    vector<int> nums(n);
    for(auto& num:nums)
    {
        cin>>num;
    }
    int target;
    cin>>target;
    int sum=0;
    idx[0]=-1;

    int res=0;
    for(int i=0;i<n;++i)
    {
        sum+=nums[i];
        if(!idx.count(sum)) idx[sum]=i;
        if(idx.count(sum-target))
        {
            res=max(i-idx[sum-target],res);
        }
    }
    cout<<res;
    system("pause");
    return 0;
}