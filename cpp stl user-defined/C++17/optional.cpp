#include<optional>
#include<iostream>
#include<map>
using namespace std;

map<int,string> user_map={{1,"cxx"},{2,"x"},{3,"c"}};

optional<string> FindUserName(int id)
{
    if(user_map.count(id))
    {
        return user_map[id];
    }
    else return nullopt;
}

int main()
{
    optional<string> res_tmp=FindUserName(1);
    string res;
    if(res_tmp.has_value())
    {
        res=*(res_tmp);
        cout<<res<<endl;
    }
    else cout<<"false"<<endl;
    system("pause");
    return 0;
}