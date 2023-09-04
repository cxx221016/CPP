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
    vector<int> nums(n);
    for(auto& num:nums)
    {
        cin>>num;
    }
    vector<int> dp(n,1);
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<i;++j)
        {
            if(nums[i]>nums[j]) dp[i]=max(dp[i],dp[j]+1);
        }
    }
    cout<<*max_element(dp.begin(),dp.end());
    system("pause");
    return 0;
}