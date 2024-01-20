#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


void QuickSort(vector<int>& nums,int left,int right)
{
    if(left>=right) return;
    int pivot=nums[left];
    int i=left,j=right;
    while(i<j)
    {
        while(i<j&&nums[j]>=pivot) --j;
        nums[i]=nums[j];
        while(i<j&&nums[i]<=pivot) ++i;
        nums[j]=nums[i];
    }
    nums[i]=pivot;
    QuickSort(nums,left,i-1);
    QuickSort(nums,i+1,right);
}

int main()
{
    vector<int> nums{10,1203,23,343,3,5,7};
    QuickSort(nums,0,nums.size()-1);
    for(auto& num:nums)
    {
        cout<<num<<" ";
    }
    system("pause");
    return 0;
}