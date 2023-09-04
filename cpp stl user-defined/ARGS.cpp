#include<iostream>
#include<cstdarg>
using namespace std;

#define ADD(int_params,...) add(int_params,__VA_ARGS__,0)//_VA_ARGS__，这个宏可以取到变参

//求和函数
int add(int firstParam, ...)
{
	va_list arg_ptr;
	int sum = 0;
	int nArgValue;
	sum += firstParam;
	va_start(arg_ptr, firstParam);
	for (nArgValue = va_arg(arg_ptr, int); nArgValue != 0;)
	{
		sum = sum + nArgValue;
		nArgValue = va_arg(arg_ptr, int);
	}
	va_end(arg_ptr);
	return sum;
}

template<typename T>
T sum(T a)
{
	return a;
}

template<typename T, typename ...Args>
T sum(T head, Args ...args)
{
	return head + sum(args...);
}

int main()
{
	cout << add(1, 2, 3, 0) << endl;       //运行结果：6
    cout<< sum(1, 2, 3, 0) << endl;
	cout << "ADD = " << ADD(1, 2, 3, 4, 5) << endl;
	system("pause");
}
