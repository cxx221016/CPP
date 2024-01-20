#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <type_traits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <optional>
#include <windows.h>
// #include"json.hpp"
using namespace std;





/*
template <typename T>
struct is_printable
{
private:
	template <class U>
	static auto check(int) -> decltype(std::declval<std::basic_ostream<char>>() << std::declval<U>(), std::true_type());
	template <class U>
	static std::false_type check(...);

public:
	static constexpr bool value{decltype(check<T>(0))::value};
};
template <class T>
inline constexpr bool is_printable_v{is_printable<T>::value};
*/

template<typename T,typename F=void>
struct is_printable:std::false_type
{

};

template<typename T>
struct is_printable<T,std::void_t<decltype(std::declval<std::basic_ostream<char>>() << std::declval<T>()) >>:std::true_type
{

};


template<typename T>
class CNN
{
public:
	template<size_t N>
	CNN(const T (&arr)[N]);
	int len;
};

template<typename T>
template<size_t N>
CNN<T>::CNN(const T (&arr)[N])
{
	len=N;
}

template<typename T ,size_t N>
class NNN
{
public:
	NNN(const T (&arr)[N]);
	int len;
};

template<typename T,size_t N>
NNN<T,N>::NNN(const T (&arr)[N])
{
	len=N;
}

struct x1
{
	char c1;
	char c2;
	int i;
};

struct x2
{
	char c1;
	int i;
	char c2;
};

struct x3
{
	int i;
	char c1;
	char c2;
};

struct stu1 {
    char a[18];
    double b;
    char c;
    // int d;
    short e;
	char f;
	char g;
};

struct stu2 {
    char a[18];
    int b[3];
    short c;
    char d;
    int e;
    short f;
};

enum DAY {
    MON = 1, TUE, WED, THU, FRI, SAT, SUN
};
struct stu3 {
    char a[5];
    char b[3];
    enum DAY day;
    int *c;
    short d;
    int e;
};

struct stu4{
	char x;
	int y;
	double z;
	char v[6];
};

union stu5{
	int a;
	char b[5];
};

struct stu6{
	stu5 a;
	stu4 b;
	int c;
};

union stu7{
	int a;
	char b[5];
	char c[3];
	int d[3];
	double e;
	stu6 f;
};

struct stu8{
	int a;
	string b;
	double c;
};

struct stu9
{
	int a[10];
};

struct stu10
{
	char a;
	char b;
	// stu9 c;
	struct {
		stu9 a;
	} c;
};

struct stu11
{
	char a[100];
};

struct stu12
{
	int a;
	char b;
	struct {
		stu11 a;
	} c;

};



int main()
{
	cout<<"sizeof(x1) "<<sizeof(x1)<<endl;
	cout<<"sizeof(x2) "<<sizeof(x2)<<endl;
	cout<<"sizeof(x3) "<<sizeof(x3)<<endl;
	cout<<"sizeof(stu1) "<<sizeof(stu1)<<endl;
	cout<<"&(((stu1*)0)->b) "<<&(((stu1*)0)->b)<<endl;
	cout<<"sizeof(stu2) "<<sizeof(stu2)<<endl;
	cout<<"sizeof(DAY) "<<sizeof(DAY)<<endl;
	cout<<"sizeof(stu3) "<<sizeof(stu3)<<endl;
	cout<<"sizeof(stu4) "<<sizeof(stu4)<<endl;//24
	cout<<"sizeof(stu5) "<<sizeof(stu5)<<endl;//8
	cout<<"sizeof(stu6) "<<sizeof(stu6)<<endl;//40
	cout<<"sizeof(stu7) "<<sizeof(stu7)<<endl;//48
	cout<<"&((&(((stu7*)0)->f))->c) "<<&((&(((stu7*)0)->f))->c)<<endl;
	cout<<"sizeof(string) "<<sizeof(string)<<endl;
	cout<<"sizeof(stu8) "<<sizeof(stu8)<<endl;
	cout<<"sizeof(stu9) "<<sizeof(stu9)<<endl;
	cout<<"sizeof(stu10) "<<sizeof(stu10)<<endl;
	cout<<"&(((stu10*)0)->c) "<<&(((stu10*)0)->c)<<endl;
	cout<<"sizeof(stu11) "<<sizeof(stu11)<<endl;
	cout<<"sizeof(stu12) "<<sizeof(stu12)<<endl;
	cout<<"&(((stu12*)0)->c) "<<&(((stu12*)0)->c)<<endl;
	auto ptr=new (std::nothrow) int[1000000000000000000ll];
	if(ptr==nullptr)
	{
		cout<<"new failed"<<endl;
	}
	else
	{
		cout<<"new success"<<endl;
	}
	system("pause");
	return 0;

}


/*
int main()
{
	int x=0x11111111;
	uintptr_t y=reinterpret_cast<uintptr_t>(&x);
	std::cout<<(int)*reinterpret_cast<char*>(y)<<endl;
	std::cout<<(int)*reinterpret_cast<char*>(y+1)<<endl;
	std::cout<<(int)*reinterpret_cast<char*>(y+2)<<endl;
	std::cout<<(int)*reinterpret_cast<char*>(y+3)<<endl;

	system("pause");
	return 0;
}*/