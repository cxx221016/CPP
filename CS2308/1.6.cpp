#include<vector>
#include<iostream>
#include<numeric>
#include<algorithm>
#include<set>
#include<unordered_map>
#include<queue>
#include<deque>
using namespace std;

class BIT {
private:
    vector<int> tree;
    int n;

public:
    BIT(int _n): n(_n), tree(_n + 1) {}

    static int lowbit(int x) {
        return x & (-x);
    }

    int query(int x) {
        int ret = 0;
        while (x) {
            ret += tree[x];
            x -= lowbit(x);
        }
        return ret;
    }

    void update(int x) {
        while (x <= n) {
            ++tree[x];
            x += lowbit(x);
        }
    }
};


int main()
{
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i=0;i<n;++i)
    {
        cin>>nums[i];
    }

    set<int> sort{nums.begin(),nums.end()};
    unordered_map<int,int> index;
    int idx=n;
    for(auto& num:sort)
    {
        index[num]=idx--;
    }
    
    BIT bit(n);
     
    deque<int> que;

    for(int i=n-1;i>=0;--i)
    {
        int curidx=index[nums[i]];
        que.push_front(bit.query(curidx-1));
        bit.update(curidx);
    }

    for(auto& res:que)
    {
        cout<<res<<" ";
    }
    
    system("pause");
    return 0;
}