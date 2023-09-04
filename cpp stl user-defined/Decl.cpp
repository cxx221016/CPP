#include<type_traits>
#include<iostream>
#include<utility>
#include<string>
#include<chrono>
#include<memory>

using namespace std::string_literals;
template<typename T>
void f1(T&& t)
{
    using F=std::decay_t<T>;
    std::cout<<"const string&: "<<std::is_same_v<T,const std::string&> <<std::endl;
    std::cout<<"string &: "<<std::is_same_v<T,std::string&> <<std::endl;
    std::cout<<"string &&: "<<std::is_same_v<T,std::string&&> <<std::endl;
    std::cout<<"const string &&: "<<std::is_same_v<T,const std::string&&> <<std::endl;
    std::cout<<"string: "<<std::is_same_v<T,std::string> <<std::endl;
    std::cout<<"const string: "<<std::is_same_v<T,const std::string> <<std::endl;
    std::cout<<"const char*: "<<std::is_same_v<T,const char*> <<std::endl;
    std::cout<<"const char*&: "<<std::is_same_v<T,const char*&> <<std::endl;
    std::cout<<"const char*&&: "<<std::is_same_v<T,const char*&&> <<std::endl;
    std::cout<<"const char*: "<<std::is_same_v<F,const char*> <<std::endl;
    std::cout<<"const char[]: "<<std::is_same_v<T,const char[]> <<std::endl;
    std::cout<<"const char[5]: "<<std::is_same_v<T,const char[5]> <<std::endl;
    std::cout<<"const char(&)[5]: "<<std::is_same_v<T,const char(&)[5]> <<std::endl;
    std::cout<<"char*: "<<std::is_same_v<T,char*> <<std::endl;
    std::cout<<"char[]: "<<std::is_same_v<T, char[]> <<std::endl;
    std::cout<<"char[5]: "<<std::is_same_v<T,char[5]> <<std::endl;
    std::cout<<"const int&: "<<std::is_same_v<T,const int&> <<std::endl;
    std::cout<<"int &: "<<std::is_same_v<T,int&> <<std::endl;
    std::cout<<"int &&: "<<std::is_same_v<T,int&&> <<std::endl;
    std::cout<<"const int &&: "<<std::is_same_v<T,const int&&> <<std::endl;
    std::cout<<"int: "<<std::is_same_v<T,int> <<std::endl;
    std::cout<<"const int: "<<std::is_same_v<T,const int> <<std::endl;
    std::cout<<"std::shared_ptr<int>: "<<std::is_same_v<T,std::shared_ptr<int>> <<std::endl;
    std::cout<<"std::shared_ptr<int>&: "<<std::is_same_v<T,std::shared_ptr<int>&> <<std::endl;
    std::cout<<"std::shared_ptr<int>&&: "<<std::is_same_v<T,std::shared_ptr<int>&&> <<std::endl;
    std::cout<<"const std::shared_ptr<int>&: "<<std::is_same_v<T,const std::shared_ptr<int>&> <<std::endl;
    std::cout<<"--------------------------------------------------"<<std::endl;

}

template<typename T>
void f2(T&& t)
{
    f1(std::forward<T>(t));
    //f1(t);
}

int main()
{
    std::string s="hello";
    f2(s);
    f2(std::move(s));
    f2("hell");
    using TY=decltype("hell");
    f2("hello"s);
    f2(1);
    f2(std::make_shared<int>(1));
    system("pause");
    return 0;
}