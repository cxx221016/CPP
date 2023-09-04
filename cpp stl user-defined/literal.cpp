/*
#include<string>
#include<iostream>
using std::cin,std::cout,std::endl;

long double operator""_E(long double x)
{ 
    return x;
}
long double operator""_a(long double x)
{
    return x;
}
int operator""_p(unsigned long long x)
{
    return x;
}
 
auto y = 1.0_a+2.0;   // OK
auto z = 1.0_E +2.0;  // OK
auto q = (1.0_E)+2.0; // OK
auto u = 1_p +2;      // OK

int main()
{
    cout<<y<<" "<<z<<" "<<q<<" "<<u<<endl;
    system("pause");
    return 0;
}

*/

#include <iostream>
#include <string>
using std::cout;

namespace cxx
{
	namespace literal
	{
		void operator"" __cout(const char* str)
		{
			std::cout<<str<<'\n';
		}

		constexpr int operator"" _round(long double d)
		{
			return static_cast<int>(d+0.5);
		}
	}
}

namespace test
{
	struct My_type
	{
		double value;
		void print() const { cout << "print value: " << value << '\n'; }
	};
	namespace literal
	{
		  // 输出 整型 和 浮点型
		void operator"" _output(const char* num)
		{
			cout << "output: " << num << '\n';
		}
		  // 类型转换
		inline My_type operator"" _to_My_type(unsigned long long num)
		{
			My_type tmp;
			tmp.value = num;
			return tmp;
		}
		  // 四舍五入
		constexpr int operator"" _round(long double num)
		{
			return int( num + 0.5 );
		}
		  // 获取字符的 ASCII 码
		constexpr int operator"" _get_ascii(char c)
		{
			return int(c);
		}
		  // 获取字符串长度
		constexpr size_t operator"" _get_len(const char* s, size_t len)
		{
			return len;
		}
	}
}

  // 一般来说，字面量容易重名，所以常常放在命名空间里
using namespace test::literal;
int main()
{
	114514_output;
	3.14_output;
	2022_to_My_type .print();  // 注意这里的空格
	cout <<  "round: " <<   9.86_round;
	cout <<   "\n\t"   <<   9.39_round   << '\n';
	cout <<  "ascii: " << 'A'_get_ascii  << '\n';
	cout << "strlen: " << "abcd"_get_len << '\n';
    system("pause");
	return 0;
}
