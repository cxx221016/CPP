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

using namespace std;

/**
 * @brief An unordered map with integer keys and integer values.
 * 
 * The map contains the following key-value pairs:
 * 1 -> 2
 * 2 -> 4
 * 3 -> 6
 * 4 -> 1
 * 5 -> 8
 * 6 -> 3
 * 7 -> 5
 * 8 -> 7
 */
unordered_map<int, int> mp{
    {1,2},
    {2,4},
    {3,6},
    {4,1},
    {5,8},
    {6,3},
    {7,5},
    {8,7}
};

int main()
{
    string C;
    cin>>C;
    cout<<C.size()<<endl;
    string P;

    
    for(int i=0;i<C.size();i+=8)
    {
        string tmp(8,'0');
        for(int j=0;j<8;j++)
        {
            tmp[mp[j+1]-1]=C[i+j];
        }
        P.append(tmp);
    }
    cout<<P<<endl;
    system("pause");
    return 0;
}
