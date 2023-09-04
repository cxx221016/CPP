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

struct fileattr
{
	std::string limits;
	// attr() = default;
	fileattr(const std::string &l = "-rw-") : limits(l) {}
	friend std::ostream &operator<<(std::ostream &os, const fileattr &a)
	{
		os << a.limits;
		return os;
	}
};

struct dirattr
{
	std::string limits;
	// attr() = default;
	dirattr(const std::string &l = "-rw-") : limits(l) {}
};


void changecolor(stringstream &os, int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	std::string tmp = os.str();
	cout << tmp;
	SetConsoleTextAttribute(hConsole, 7);
}

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
/*
template<typename T>
inline constexpr bool is_printable_v{is_printable<T>::value};

template <typename T, typename = std::enable_if_t<is_printable_v<T>>>
void changecolor(T &&t, const int forecolor=7,const int backcolor=0)
{
	cout << "\033[" << "38;5;" << forecolor << "m";
	cout << "\033[" << "48;5;" << backcolor << "m";
	cout << t << "\033[m";
}
*/

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


int main()
{
	int cnt=0;
	for(int i=1;i<1000;++i)
	{
		if(i%3==0||i%6==0||i%14==0)
		{
			cnt++;
		}
	}
	std::cout<<cnt<<std::endl;
	std::cout<<1000-cnt<<std::endl;
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