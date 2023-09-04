#include<iostream>
#include<ratio>
#include<chrono>

int main()
{
    typedef std::chrono::duration<int> seconds_type;
    typedef std::chrono::duration<int,std::milli> milliseconds_type;
    typedef std::chrono::duration<int,std::ratio<60*60>> hours_type;

    hours_type h_oneday(25);
    seconds_type s_oneday = std::chrono::duration_cast<seconds_type>(h_oneday);
    milliseconds_type ms_oneday = std::chrono::duration_cast<milliseconds_type>(h_oneday);

    seconds_type s_onehour(60*60);
    hours_type h_onehour = std::chrono::duration_cast<hours_type>(s_onehour);
    milliseconds_type ms_onehour = std::chrono::duration_cast<milliseconds_type>(s_onehour);

    std::cout<<ms_onehour.count()<<std::endl;
    system("pause");
    return 0;
}