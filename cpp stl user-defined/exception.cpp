#include <iostream>
using namespace std;


struct Exit : runtime_error 
{
	Exit() : runtime_error("Exit") {}
};


inline void error(const string& s)
{
	throw runtime_error(s);
}

int main()
{
    try
    {
        int i;
        cin>>i;
        if(i>=10) error("upper");
        else cout<<i<<endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    system("pause");
    return 0;
}