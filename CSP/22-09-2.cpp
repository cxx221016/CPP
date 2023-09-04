#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<unordered_set>
#include<unordered_map>
#include<string>
#include<sstream>
#include<cmath>
#include<map>
#include<queue>
#include<ctime>
#include<random>
#include<fstream>
#include<stack>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,x;
    cin>>n>>x;
    vector<int> prices(n,0);
    for(auto& price:prices)
    {
        cin>>price;
    }

    int sum=accumulate(prices.begin(),prices.end(),0);
    
    vector<int> dp(sum-x+1,0);
    int om=0;
    for(int i=0;i<n;++i)
    {
        for(int j=sum-x;j>=0;--j)
        {
            if(j>=prices[i])
            {
                dp[j]=max(dp[j],dp[j-prices[i]]+prices[i]);
                om=max(om,dp[j]);
            }
        }
    }
    cout<<sum-om<<flush;
    system("pause");
    return 0;
}