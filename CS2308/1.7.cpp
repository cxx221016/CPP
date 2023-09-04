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



int main()
{
    int n;
    cin>>n;
    vector<int> nums(n+1);
    for(int i=1;i<=n;++i)
    {
        cin>>nums[i];
    }
    

    vector<int> premax(n+1,INT_MIN),premin(n+1,INT_MAX),sufmax(n+2,INT_MIN),sufmin(n+2,INT_MAX);
    premax[0]=0;
    premin[0]=0;
    for(int i=1;i<=n;++i)
    {
        premax[i]=max(nums[i],premax[i-1]+nums[i]);
        premin[i]=min(nums[i],premin[i-1]+nums[i]);
    }

    sufmax[n+1]=0;
    sufmin[n+1]=0;

    for(int i=n;i>=1;--i)
    {
        sufmax[i]=max(nums[i],sufmax[i+1]+nums[i]);
        sufmin[i]=min(nums[i],sufmin[i+1]+nums[i]);
    }
    int res=0;
    for(int i=1;i<=n-1;++i)
    {
        res=max(abs(premax[i]-sufmin[i+1]),max(res,abs(premin[i]-sufmax[i+1])));
    }
    res=max(res,accumulate(nums.begin(),nums.end(),0));
    cout<<res;
    system("pause");
    return 0;
}
