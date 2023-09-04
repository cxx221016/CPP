#include <iostream>
#include <vector>
#include <stack>
#include <functional>
#include <algorithm>
#include <cmath>
#include<set>
#include<queue>
using namespace std;
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

struct line
{
    pair<int,int> p1,p2;
    line(pair<int,int> p1,pair<int,int> p2):p1(p1),p2(p2)
    {

    }
    line()=default;
};

class BIT
{
    vector<int> nums;
public:
    BIT(int n):nums(n,0)
    {

    }

    int lowbit(int x)
    {
        return x&(-x);
    }

    void update(int i,int x=1)
    {
        while(i<nums.size())
        {
            nums[i]+=x;
            i+=lowbit(i);
        }
    }

    int query(int i)
    {
        int res=0;
        while(i)
        {
            res+=nums[i];
            i-=lowbit(i);
        }
        return res;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<line> hlines;
    vector<line> vlines;
    vector<int> ally;
    for(int i=0;i<n;++i)
    {
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1==x2)
        {
            vlines.emplace_back(make_pair(x1,min(y1,y2)),make_pair(x1,max(y1,y2)));
            ally.push_back(y1);
            ally.push_back(y2);
        }
        else
        {
            hlines.emplace_back(make_pair(min(x1,x2),y1),make_pair(max(x1,x2),y1));
            ally.push_back(y1);
        }
    }
    set<int> yset(ally.begin(),ally.end());
    unordered_map<int,int> ymap;
    int cnt=1;
    for(auto y:yset)
    {
        ymap[y]=cnt++;
    }
    for(auto& l:vlines)
    {
        l.p1.second=ymap[l.p1.second];
        l.p2.second=ymap[l.p2.second];
    }
    for(auto& l:hlines)
    {
        l.p1.second=ymap[l.p1.second];
        l.p2.second=ymap[l.p2.second];
    }
    sort(vlines.begin(),vlines.end(),[](const line& l1,const line& l2)
    {
        return l1.p1.first==l2.p1.first? l1.p1.second<l2.p1.second:l1.p1.first<l2.p1.first;
    });
    sort(hlines.begin(),hlines.end(),[](const line& l1,const line& l2)
    {
        return l1.p1.first==l2.p1.first? l1.p1.second<l2.p1.second:l1.p1.first<l2.p1.first;
    });

    auto cmp=[](const line& l1,const line& l2)
    {
        return l1.p2.first>l2.p2.first;
    };
    priority_queue<line,vector<line>,decltype(cmp)> que(cmp);
    BIT bit(cnt);
    int res=0;
    int j=0;
    for(auto& l:vlines)
    {
        int x1=l.p1.first;
        for(;j<hlines.size()&&hlines[j].p1.first<=x1;++j)
        {
            bit.update(hlines[j].p1.second);
            que.push(hlines[j]);
        }
        while(!que.empty()&&que.top().p2.first<x1)
        {
            bit.update(que.top().p1.second,-1);
            que.pop();
        }
        res+=bit.query(l.p2.second)-bit.query(l.p1.second-1);
    }
    cout << res << endl;
    system("pause");
    return 0;

}