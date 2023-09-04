#include<iostream>
#include<string>
#include<regex>
using namespace std;

int main()
{
    string str;
    regex pattern("\\b[\\w%.+-]+@[\\w.-]+\\.[a-zA-Z]{2,6}\\b");
    while(getline(cin,str))
    {
        smatch results;
        if(regex_search(str,results,pattern))
        {
            for(auto& result:results)
            {
                cout<<result<<" , ";
            }
            cout<<endl;
        }
        else cout<<"Not find\n";
    }
    system("pause");
    return 0;
}