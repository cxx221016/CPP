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
    int n,m;
    cin>>n>>m;
    vector<int> nums(n);
    for(auto& num:nums)
    {
        cin>>num;
    }
    int c=1;
    for(int i=0;i<n;++i)
    {
        int nc=c*nums[i];
        cout<<(m%nc)/c<<" ";
        c=nc;
    }
    cout<<flush;
    system("pause");
    return 0;
}