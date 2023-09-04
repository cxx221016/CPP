#include<vector>
#include<iostream>
#include<numeric>
#include<algorithm>
#include<set>
using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<int> nums(n);
    for(auto& num:nums)
    {
        cin>>num;
    }
    set<int> res;
    int sum=accumulate(nums.begin(),nums.end(),0);
    if(sum==0) res.insert(0);
    int pre=0,suf=sum-nums[0];
    if(pre==suf) res.insert(0);
    for(int i=1;i<n;++i)
    {
        pre+=nums[i-1];
        suf-=nums[i];
        if(pre==suf) res.insert(i);
        if(i==n-1&& pre==0) res.insert(i);
    }
    for(auto& pos:res)
    {
        cout<<pos<<" ";
    }
    system("pause");
    return 0;
}