#include<vector>
#include<unordered_map>
#include<iostream>

using namespace std;

namespace std {
template<>
class hash<vector<int>> 
{
public:
    size_t operator()(const vector<int> &p) const {
        size_t seed=p.size();
        for(auto& i:p)
        {
            seed^=i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
};

namespace std {
template<>
class hash<pair<int,int>> 
{
public:
    size_t operator()(const pair<int,int> &p) const {
        return hash<int>()(p.first)^hash<int>()(p.second);
    }
};
};


namespace std {
template<>
class hash<tuple<int,int,int>> 
{
public:
    size_t operator()(const tuple<int,int,int> &p) const {
        auto&& [x,y,z]=p;
        return (hash<int>()(x)<<24^hash<int>()(y)<<8^hash<int>()(z));
    }
};
};



static constexpr auto tpl_hash=[f=hash<int>()](const tuple<int,int,int>& entry)->size_t
{
    auto&& [x,y,z]=entry;
    return (f(x)<<24^f(y)<<8^f(z));
};
int idx=0;
unordered_map<tuple<int,int,int>,pair<int,int>,decltype(tpl_hash)> seen{0,tpl_hash};

int main()
{
    unordered_map<pair<int,int>,int> mp1;
    unordered_map<vector<int>,int> mp2;
    unordered_map<tuple<int,int,int>,pair<int,int>> mp3;
    mp1[{1,2}]=1;
    mp1[{2,1}]=2;
    for(auto& [pr,dis]:mp1)
    {
        cout<<pr.first<<" "<<pr.second<<" "<<dis<<endl;
    }
    system("pause");
}
