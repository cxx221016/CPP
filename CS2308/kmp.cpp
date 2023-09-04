#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include<cmath>
using namespace std;

int kmp_count(string s,string t)
{
    int res=0;
    int ns=s.size(),nt=t.size();
    vector<int> next(nt,-1);
    for(int j=-1,i=1;i<nt;++i)
    {
        while(j>=0&&t[i]!=t[j+1])
        {
            j=next[j];
        }
        if(t[i]==t[j+1]) ++j;
        next[i]=j;
    }

    for(int i=0,j=-1;i<ns;++i)
    {
        while(j>=0&&s[i]!=t[j+1])
        {
            j=next[j];
        }
        if(s[i]==t[j+1]) ++j;
        if(j==nt-1)
        {
            res++;
            i-=nt-1;
            j=-1;
        }
    }
    return res;
}


bool kmp(string s,string t)
{
    int ns=s.size(),nt=t.size();
    vector<int> next(nt,-1);
    for(int j=-1,i=1;i<nt;++i)
    {
        while(j>=0&&t[i]!=t[j+1])
        {
            j=next[j];
        }
        if(t[i]==t[j+1]) ++j;
        next[i]=j;
    }

    for(int i=0,j=-1;i<ns;++i)
    {
        while(j>=0&&s[i]!=t[j+1])
        {
            j=next[j];
        }
        if(s[i]==t[j+1]) ++j;
        if(j==nt-1) return true;
    }
    return false;
}
 
int main()
{
    string s;
    string t;
    while(true)
    {
        cin>>s>>t;
        cout<<kmp(s,t)<<' ';
        cout<<kmp_count(s,t)<<'\n';
    }
    system("pause");
    return 0;
}
 