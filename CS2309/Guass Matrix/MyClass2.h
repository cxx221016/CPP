#include <exception>

class MyClass2: public exception  
{  
public:

    virtual const char* what() const throw()  
    {  
        return "error2";  
    }  
};