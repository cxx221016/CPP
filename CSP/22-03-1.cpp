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
    int n,k;
    cin>>n>>k;
    unordered_set<int> seen;
    int i,j;
    int res=0;
    while(k--)
    {
        cin>>i>>j;
        if(j==0||seen.count(j)) {}
        else res++;
        seen.insert(i);
    }
    cout<<res<<flush;
    system("pause");
    return 0;
}