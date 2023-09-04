#include<iostream>
#include<set>
#include<cmath>
using namespace std;

int guassfunction(int n)
{
    double res=n;
    set<int> seen;
    int i=2;
    while(n>1&&i<sqrt(n))
    {
        if(n%i==0)
        {
            n/=i;
            seen.insert(i);
        }
        else
        {
            i++;
        }
    }

    for(auto& fact:seen)
    {
        res=res*(double)(1.0-1.0/(double)fact);
    }
    return (int)res;
}

int main()
{
    int n;
    while(cin>>n)
    {
        cout<<guassfunction(n)<<endl;
    }
    return 0;
}