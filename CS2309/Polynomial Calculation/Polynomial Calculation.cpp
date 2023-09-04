#include "std_lib_facilities.h"
#include "Polynomial.h"
#include<regex>
//请根据自己需求定义Polynomial
//定义main函数

int main()
{
    /********** Begin **********/
    //读取测试输入
    string str;
    string strx;
    cin>>str>>strx;
    regex polyPattern("^([-+]?([0-9]*\.?[0-9]+)?(x(\\^[+-]?[0-9]+)?)?)+$"); 
        if(!regex_match(str,polyPattern))
        { 
            cout<<"error";
            return 0;
        }
    Polynomial<Type> L(str);
    //请打印输出运算结果
    double x=stof(strx);
    cout<<fixed<<setprecision(4)<<keep(L.Cal(x));
	/********** End **********/
    system("pause");
  	return 0;
}