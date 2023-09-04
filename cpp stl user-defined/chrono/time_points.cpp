#include<iostream>
#include<ratio>
#include<chrono>

int main()
{
    using namespace std::chrono;
    /*
    system_clock::time_point tp_epoch;
    time_point<system_clock,duration<int>> tp_seconds(duration<int>(1));
    system_clock::time_point tp(tp_seconds);

    std::cout<<"1 second since epoch: "<<tp.time_since_epoch().count()<<std::endl;
    std::time_t tt=system_clock::to_time_t(tp);
    std::cout<<"time_point tp is "<<ctime(&tt)<<std::endl;
    */

   typedef duration<int,std::ratio<60*60*24>> days_type;
   time_point<system_clock,days_type> today=time_point_cast<days_type>(system_clock::now());
   std::cout<<"today is "<<today.time_since_epoch().count()<<" days since epoch"<<std::endl;
    system("pause");
    return 0;
}