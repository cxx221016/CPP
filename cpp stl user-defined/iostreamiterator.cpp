#include<vector>
#include<iostream>
#include<iterator>
using namespace std;

int main()
{
    vector<int> nums(3);
    istream_iterator<int> ini(cin);
    istream_iterator<int> eof;
    copy(ini,eof,nums.begin());
    ostream_iterator<int> osi(cout,",");
    copy(nums.begin(),nums.end(),osi);
    system("pause");
    return 0;
}