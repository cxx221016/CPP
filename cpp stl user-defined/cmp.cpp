#include<vector>
#include<unordered_map>
#include<map>
#include<iostream>


namespace std {
template<>
class less<pair<int,int>>
{
public:
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const 
    {
        return a.second == b.second ? (a.first < b.first) : (a.second < b.second);
    }
};
};


using namespace std;
int main()
{
    map<pair<int,int>,int> mp;
    pair<int,int> p2{1,2};
    pair<int,int> p1{2,1};
    mp[p2]=2;
    mp[p1]=1;
    for(auto& [_,rank]:mp)
    {
        cout<<rank<<endl;
    }
    system("pause");
    return 0;

}

