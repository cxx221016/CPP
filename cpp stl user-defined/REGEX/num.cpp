#include<iostream>
#include<string>
#include<regex>
using namespace std;

int main()
{
    string str;
    string z_0_num="^[0,9]*$";//前导0
    string z_num="^([0-9]|[1-9][0-9]*)$";//无前导0
    string num="^(-?([0-9]|[1-9][0-9]*))$";//正数负数
    string n_num="^\\d{5}$";//五位数字
    string more_n_num="^\\d{5,}$";//五位数字以上
    string FLOAT="^(-?\\d+)(\\.\\d+)$";//浮点
    regex pattern(FLOAT);
    while(getline(cin,str))
    {
        if(regex_match(str,pattern))
        {
            cout<<str<<endl;
        }
        else cout<<"Not find\n";
    }
    system("pause");
    return 0;
}