#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<unordered_set>
#include<unordered_map>
#include<set>
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
#define DEBUG
//gcc -S ./shiyan/shiyan3.cpp -o ./shiyan/shiyan3.s

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class NestedInteger {
public:
   // Constructor initializes an empty nested list.
   NestedInteger();

   // Constructor initializes a single integer.
   NestedInteger(int value);

   // Return true if this NestedInteger holds a single integer, rather than a nested list.
   bool isInteger() const;

  // Return the single integer that this NestedInteger holds, if it holds a single integer
   // The result is undefined if this NestedInteger holds a nested list
   int getInteger() const;

   // Set this NestedInteger to hold a single integer.
   void setInteger(int value);

   // Set this NestedInteger to hold a nested list and adds a nested integer to it.
   void add(const NestedInteger &ni);

   // Return the nested list that this NestedInteger holds, if it holds a nested list
   // The result is undefined if this NestedInteger holds a single integer
   const vector<NestedInteger> &getList() const; 
};

class Token
{
    string expression;
    int idx;
    set<string> item()
    {
        set<string> res;
        if(expression[idx]=='{')
        {
            idx++;
            res=expr();
        }
        else 
        {
            res={string(1,expression[idx])};
        }
        idx++;
        return move(res);
    }
    set<string> term()
    {
        set<string> res={""};
        while(idx<expression.size()&& (expression[idx]=='{'||isalpha(expression[idx])))
        {
            auto sub=item();
            set<string> tmp;
            for(auto& left:res)
            {
                for(auto& right:sub)
                {
                    tmp.insert(left+right);
                }
            }
            res=move(tmp);
        }
        return move(res);
    }
    set<string> expr()
    {
        set<string> res;
        while(true)
        {
            res.merge(term());
            if(idx<expression.size()&&expression[idx]==',')
            {
                idx++;
                continue;
            }
            else break;
        }
        return move(res);
    }
public:
    vector<string> braceExpansionII(string expression) {
        this->expression = expression;
        this->idx = 0;
        auto ret = expr();
        return {ret.begin(), ret.end()};
    }
};

class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int n=nums.size();
        int res=0;
        int l=0,r=0;
        int cnt=0;
        while(r<n)
        {
            if(nums[r]>=left&&nums[r]<=right)
            {
                cnt=r-l+1;
            }
            else if(nums[r]<left)
            {
                cnt=cnt;
            }
            else if(nums[r]>right)
            {
                l=r+1;
                cnt=0;
            }
            res+=cnt;
            r++;
        }
        return res;
    }
};

int main()
{
    
    int n=10;
    while(n--)
    {
        uintptr_t tmp;
        std::cout<<(&tmp)<<std::endl;
    }
    system("pause");
    return 0;
}




