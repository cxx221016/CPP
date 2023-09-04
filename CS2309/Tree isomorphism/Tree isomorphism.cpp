#include "std_lib_facilities.h"
#include "MyClass.h"
int main()
{
    /********** Begin **********/
    //读取测试输入
    istringstream is;
    ostringstream os;
    char ch;
    string input;
    while((ch=cin.get())!=EOF)  input.push_back(ch);
    is.str(input);
    string s;
    string t;
    is>>s;
    is>>t;
    MySolution S;
    bool flags=S.isvalid(s);
    bool flagt=S.isvalid(t);
    if(!flags||!flagt)
    {
        os<<"Invalid tree(s): "<<(flags? "":s )<<(!flags&&!flagt ? " ":"")<<(flagt? "":t );
    }
    string cmp=S.my_isomorphic(s,t);
    if(cmp=="1")
    {
        os<<s<<" and "<<t<<" are isomorphic";
    }
    else if(cmp=="0")
    {
        os<<s<<" and "<<t<<" are non-isomorphic";
    }
    else 
    {
        
    }
    string output=os.str();
    //请打印输出结果
    cout<<input.size()-1<<":"<<output.size()<<'\n';
    cout<<output<<endl;

	/********** End **********/
    system("pause");
  	return 0;
}