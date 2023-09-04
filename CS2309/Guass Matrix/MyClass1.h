#include <exception>

class MyClass1: public exception  
{  
public:
    virtual const char* what() const throw()  
    {  
        return "error1";  
    }  
};