#include <iostream>
#include <functional>
#include<unordered_map>
using namespace std;

int Plus(int a, int b)
{
     return a+b;
}

struct struct_Plus
{
public:
    int operator() (int a, int b)
    {
        return a + b;
    }
};

template<class T>
struct template_struct_Plus
{
public:
    T operator() (T a, T b)
    {
        return a + b;
    }
};

class class_Plus
{
public:
    class_Plus(int num_):num(num_){}
    static int static_Plus(int a,int b)
    {
        return a+b;
    }
	int Plus(int a, int b)
	{
	    return a + b;
	}
	int  num;
};

int main()
{
    function<int(int,int)> f(Plus); //函数调用
    function<int(int,int)> struct_f(struct_Plus);//仿函数调用
    function<int(int,int)> struct_Temporary_object_f(struct_Plus());//仿函数临时对象调用
    function<int(int,int)> template_struct_f(template_struct_Plus<int>);//仿函数调用
    function<int(int,int)> template_struct_Temporary_object(template_struct_Plus<int>());//仿函数临时对象调用

    class_Plus p(4);
    function<int(int, int)> class_static_function_f = &class_Plus::static_Plus; //类静态成员函数
    function<int(class_Plus&,int, int)> class_function_f_1 = &class_Plus::Plus; // 类成员函数
    function<int(const class_Plus,int, int)> class_function_f_2= &class_Plus::Plus; // 类成员函数
    function<int(const class_Plus&)> class_num_f_1 = &class_Plus::num; //类成员
    function<int(const class_Plus)> class_num_f_2 = &class_Plus::num; //类成员
    auto class_num_f_3=std::mem_fn( &class_Plus::num);
    function<int(int,int)> bind_class_f = bind(&class_Plus::Plus, &p, placeholders::_1, placeholders::_2);  //bind
    auto class_function_f_3=std::mem_fn(&class_Plus::Plus);
    cout<<class_function_f_3(p,3,4)<<endl;

    unordered_map<char, function<int(int, int)>> binops = 
	{
		{ '+', f },
		{ '-', [](int i, int j){return i - j; } },
	};
    cout<<class_num_f_1(p);
    int x=1;
    auto tryfun=[&x](int a,int b){return a+b+x;};
    system("pause");                                       
    return 0;
}
