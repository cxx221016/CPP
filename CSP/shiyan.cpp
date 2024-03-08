#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<functional>
using namespace std;


int main()
{
    int i=0;
    vector<int> nums(10);

    istream_iterator<int> is(cin);
    copy_n(is,10,nums.begin());
    

    for_each(nums.begin(),nums.end(),[&](int& x)
    {
        x=i++;
    });

    ostream_iterator<int> os(cout,",");
    copy(nums.begin(),nums.end(),os);
    cout<<'\n';

    for_each(nums.begin(),nums.end(),bind([](int &x,int place)
    {
        x+=place;
    },placeholders::_1,3));
    copy(nums.begin(),nums.end(),os);
    system("pause");
    return 0;
}