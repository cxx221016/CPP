#include<string>
#include<sstream>
#include<unordered_map>
#include<iterator>
#include<iostream>
#include<tuple>
#include<vector>

template<typename T>
inline auto format(T&& t)->std::string
{
    std::ostringstream os;
    os<<t;
    return os.str();
}

template<typename... T>
inline auto format(const std::string& fmt, T&&... args)->std::string
{
    //return fmt+format(args...);
    std::vector<std::string> vec{format(std::forward<T>(args))...};
    constexpr size_t n=sizeof...(T);
    std::ostringstream os;
    for(size_t i=0;i<fmt.size();++i)
    {
       if(fmt[i]=='{')
       {
           size_t j=i+1;
           while(j<fmt.size()&&fmt[j]!='}') ++j;
           if(j==fmt.size()) throw std::runtime_error("format error");
           std::string num;
           if(j==i+1) num="0";
           else num=fmt.substr(i+1,j-i-1);
           //if(num.empty()) throw std::runtime_error("format error");
           size_t idx=std::stoi(num);
           if(idx>=n) throw std::runtime_error("format error");
            os<<vec[idx];
            i=j;
       }
       else if(fmt[i]=='}')
       {
              throw std::runtime_error("format error");
       }
       else os<<fmt[i];
    }
    return os.str();
}

/*

template<typename T,typename... Args>
inline auto format(T&& t,Args&&... args)->std::string
{
    //std::cout<<"1"<<std::endl;
    std::ostringstream os;
    os<<t;
    constexpr size_t n=sizeof...(Args);
    if constexpr(n==0) return os.str();
    else  return os.str()+format(args...);
}
*/
int main()
{
    try
    {
        std::cout<<format("hello {1} {2}","world",1,"str");
        std::cout<<format("hello {1} {2}","world",1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        system("pause");
        return 0;
    }

    system("pause");
    return 0;
}