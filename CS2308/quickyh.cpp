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
#include<ctime>
// #include"json.hpp"
using namespace std;


int f(int n)
{
    
	cout<<n<<" ";
	int pre=1;
	for(int i=2;i<=n;++i)
	{
		pre^=i;
	}
	cout<<pre<<" ";
    
    int res=0;
	for(int k=0,mulk=1;n>=mulk;++k,mulk*=2)
	{
		int cnt=(n/(mulk*2))*mulk+min(max(n%(mulk*2)-mulk+1,0),mulk);
        if(cnt%2==1) res|=(1<<k);
	}
	cout<<res<<endl;
	return res;
}

int main()
{
	srand(time(nullptr));
	for(int i=0;i<10;++i)
	{
		f(rand()%99+1);
	}
	
	system("pause");
	return 0;
}

