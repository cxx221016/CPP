#pragma once
#include<vector>
#include<algorithm>
using namespace std;

/*
*@brief Binary Indexed Tree
*@param nums: the array to be operated
*@param lowbit: get the lowbit of a number
*@param update: update the value of nums[i] by x
*@param query: get the sum of nums[1]~nums[i]
*/
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

