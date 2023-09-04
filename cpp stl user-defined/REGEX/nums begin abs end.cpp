#include<iostream>
#include<string>
#include<regex>
using namespace std;

int main()
{
    string str;
    regex pattern("[0-9]+abc");
    while(cin>>str)
    {
        smatch results;
        if(regex_search(str,results,pattern))
        {
            cout<<results[0]<<endl;
        }
        else cout<<"Not find\n";
    }
    system("pause");
    return 0;
}