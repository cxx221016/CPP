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
#include <cxxabi.h>
#include <typeinfo>

using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


struct Node
{
    TreeNode* node;
    TreeNode* father;
    Node(TreeNode* node,TreeNode* father):node(node),father(father){}
};
/*


const char *TypeToName(const char *name)
{
    const char *__name = abi::__cxa_demangle(name, nullptr, nullptr, nullptr);
    return __name;
}
*/
/*
int main(int argc, char *argv[])
{
    std::cout << TypeToName(typeid(char).name()) << std::endl;
    std::cout << TypeToName(typeid(int).name()) << std::endl;
    std::cout << TypeToName(typeid(double).name()) << std::endl;

    std::cout << "----------" << std::endl;

    std::cout << TypeToName(typeid(const char*).name()) << std::endl;
    std::cout << TypeToName(typeid(const char []).name()) << std::endl;

    std::cout << "----------" << std::endl;

    std::cout << TypeToName(typeid(std::string).name()) << std::endl;
    std::cout << TypeToName(typeid(const std::string&).name()) << std::endl;
    std::cout << typeid(const std::string&).name() << std::endl;
    std::cout << typeid(std::string).name() << std::endl;
    system("pause");
}
*/

void hanoi(int n,char src,char tmp,char dst)
{
    if(n==1)
    {
        cout<<src<<"->"<<dst<<endl;
    }
    else
    {
        hanoi(n-1,src,dst,tmp);
        cout<<src<<"->"<<dst<<endl;
        hanoi(n-1,tmp,src,dst);
    }
}

struct B
{
    virtual void f() const
    {
        cout<<"B::f()"<<endl;
    }
};

struct D:public B
{
    void f() const override
    {
        cout<<"D::f()"<<endl;
    }
};

int main()
{
    B* p=new D;
    p->f();

    system("pause");
    return 0;
}

