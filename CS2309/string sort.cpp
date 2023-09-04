#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<string>
#include<sstream>
#include<unordered_map>
#include<iterator>
using namespace std;

int main()
{
    ostringstream os;
    unordered_set<string> seen;
    unordered_map<string,int> getidx;
    vector<string> strs;
    string str;
    while(getline(cin,str))
    {
        if(!seen.count(str))
        {
            strs.push_back(str);
            getidx[str]=strs.size()-1;
            seen.insert(str);
        }
    }

    os<<"rule a:"<<'\n';
    sort(strs.begin(),strs.end(),[](const string& a,const string& b)
    {
        return a<b;
    });

    for(auto& str:strs)
    {
        os<<str<<'\n';
    }
  
    os<<"rule b:"<<'\n';
    sort(strs.begin(),strs.end(),[&](const string& a,const string& b)
    {
        string ta=a;
        string tb=b;
        transform(ta.begin(),ta.end(),ta.begin(),::tolower);
        transform(tb.begin(),tb.end(),tb.begin(),::tolower);
        return ta==tb? getidx[a]>getidx[b] : ta>tb;
    });

    for(auto& str:strs)
    {
        os<<str<<'\n';
    }

    string output=os.str();
    output.pop_back();
    cout<<output;
    system("pause");
    return 0;
}