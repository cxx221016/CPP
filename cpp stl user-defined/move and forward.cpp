
#include<string>
#include<iostream>
#include<type_traits>
#include <utility>
#include <chrono>
class Teacher
{
private:
    std::string name;
    std::string position;

public:
    template <typename S1, typename S2 = std::string ,typename = std::enable_if_t<std::is_convertible_v<S1, std::string>>>
    Teacher(S1&& n, S2&& p = "lecturer"): name(std::forward<S1>(n)), position(std::forward<S2>(p)) {};

    friend std::ostream& operator<<(std::ostream& os,const Teacher& t)
    {
        os<<t.name<<" "<<t.position<<std::endl;
        return os;
    }
};

using std::operator"" s;

int main()
{
    Teacher t1("david"s);
    Teacher t2 = Teacher("david"s);
    Teacher t3=Teacher("cxx","math"s);
    Teacher t4=t3;
    Teacher t5 = Teacher{ "lily"s };
 
    auto t6 = Teacher("david"s);
    auto t7 = Teacher{ "lily"s };
    std::cout<<t1<<t2<<t3<<t4<<t5<<t6<<t7<<std::endl;
    system("pause");
    return 0;
}

