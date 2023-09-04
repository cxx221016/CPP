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
    int clone=n;
    unordered_map<int,int> mp;
    int tmp;
    while(n--)
    {
        cin>>tmp;
        mp[tmp]++;
        if(mp[tmp]>clone/2)
        {
            cout<<tmp;
            return 0;
        }
    }
    system("pause");
    return 0;
}