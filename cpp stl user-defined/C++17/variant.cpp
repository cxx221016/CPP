#include<variant>
#include<iostream>
#include<string>
using namespace std;

/*
template<typename T>
class Node
{
    T val;
    Node* next;

public:
    Node()=default;
    Node(T _val=0):val(_val),next(nullptr)
    {

    };
    template<typename U>
    Node(const Node<U>& ot)
    {
        val=ot.val;
        next=ot.next;
    }
    friend ostream& operator<<(ostream& os,const Node<T>& node)
    {
        os<<node.val;
        return os;
    }
};
*/

typedef int(*func) (int);

int print(int x=0)
{
    cout<<"print(x): "<<x<<"  "<<endl;
    return 1;
}

union 
{
    void* addr_char;
    uintptr_t* addr_int;
    func f;
} unn;

int main()
{
    unn.f=&print;
    unn.f(1);
    cout<<"raw: "<<(void*)&print<<endl;
    cout<<"char: "<<unn.addr_char<<endl;
    cout<<"int: "<<unn.addr_int<<endl;
    system("pause");
}

/*
int main()
{
    std::variant<int, int, std::string> var(in_place_index<0>,3); // sets first int to 0, index()==0
    //auto a = std::get<double>(var); // compile-time ERROR: no double
    //auto b = std::get<4>(var); // compile-time ERROR: no 4th alternative
    //auto c = std::get<int>(var); // compile-time ERROR: int twice
 
    try{
        //auto s = std::get<std::string>(var); // throws exception (first int currently set)
        auto i = std::get<0>(var); // OK, i==0
        cout<<i<<endl;
        auto j = std::get<1>(var); // throws exception (other int currently set)
    }
    catch (const std::bad_variant_access& e) 
    { // in case of an invalid access
        std::cout << "Exception: " << e.what() << '\n';
    }
    system("pause");
}*/

/*
int  main()
{
    variant<func,void*> var{in_place_index<0>,&print};
    int index=var.index();
    cout<<"index: "<<index<<endl;
    try
    {
        auto var_value0=get<0>(var);
        cout<<"var_value0: "<<var_value0(1)<<endl;
        auto var_value1=get<1>(var);
        cout<<"var_value1: "<<(var_value1)<<endl;
    }
    catch(const std::bad_variant_access& e)
    {
        std::cerr << e.what() << '\n';
    }
    /*
    auto var_value0=get<0>(var);
    cout<<"var_value0: "<<var_value0(1)<<endl;
    auto var_value1=get<1>(var);
    cout<<"var_value1: "<<(var_value1)<<endl;
    */
    /*
    auto var_value2=get<2>(var);
    cout<<"var_value2: "<<var_value2<<endl;
    */
    /*
    var="cxx";
    int index=var.index();
    cout<<"index: "<<index<<endl;
    auto var_value0=get<0>(var);
    cout<<"var_value0: "<<var_value0<<endl;
    auto var_value1=get<1>(var);
    cout<<"var_value1: "<<var_value1<<endl;
    auto var_value2=get<2>(var);
    cout<<"var_value2: "<<var_value2<<endl;
    var=Node('a');
    int index=var.index();
    cout<<"index: "<<index<<endl;
    auto var_value0=get<0>(var);
    cout<<"var_value0: "<<var_value0<<endl;
    auto var_value1=get<1>(var);
    cout<<"var_value1: "<<var_value1<<endl;
    auto var_value2=get<2>(var);
    cout<<"var_value2: "<<var_value2<<endl;
    */
    //cout<<boolalpha<<"has string: "<<holds_alternative<string>(var)<<endl;
    /*
    system("pause");
}
*/