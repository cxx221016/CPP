#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <regex>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include<complex>
#include<iomanip>

using namespace std;



int main()
{
    string P="breathtaking";
    string C="RUPOTENTOIFV";
    for(auto& p:P)
    {
        cout<<setw(3)<<p-'a'<<" ";
    }
    cout<<endl;
    for(auto& c:C)
    {
        cout<<setw(3)<<c-'A'<<" ";
    }
    system("pause");
    return 0;
}
