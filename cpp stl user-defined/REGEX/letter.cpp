#include<iostream>
#include<string>
#include<regex>
using namespace std;

int main()
{
    string str;
    regex pattern("cx*x");
    while(cin>>str)
    {
        smatch results;
        if(regex_match(str,results,pattern))
        {
            for(auto& result:results)
            {
                cout<<result<<" ";
            }
            cout<<endl;
        }
        else cout<<"Not find\n";
    }
    system("pause");
    return 0;
}