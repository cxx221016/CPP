#include<iostream>
#include<sstream>
using namespace std;

int main()
{
    istringstream is;
    ostringstream os;
    string res;
    char ch;
    while((ch=cin.get())!=EOF) res+=ch;
    is.clear();
    is.str(res);
    cout<<res.size()<<" "<<res<<endl;
    for(int i=0;i<res.size();++i)
    {
        char c;
        is>>c;
        os<<c;
    }
    string output;
    output=os.str();
    cout<<output.size()<<" "<<output;
    system("pause");
    return 0;
}