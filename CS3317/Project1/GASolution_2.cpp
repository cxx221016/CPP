#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include<utility>
#include<queue>
#include<set>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<algorithm>
#include<chrono>
#include<memory>
#include<cassert>
#include<ctime>

using namespace std;
const double tuozhan_rate=1.1;
int gapcost = 3;
int mismatchcost = 5;



inline static int getrandom(int min,int max)
{
    static auto e=default_random_engine (chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dis(min,max);
    int res=dis(e);
    return res;
}


inline pair<map<int,int>,string> tuozhan(const string& str,int new_len)
{
    map<int,int> new_pos;

    unordered_set<int> pos;
    string new_str;
    int sub_len=new_len-str.size();
//    int gaplength=(double)pow(sub_len,2)/new_len;
//
//    int gapnum=gaplength?sub_len/gaplength:0;
//    int remain=gaplength?sub_len%gaplength:0;
//    for(int i=0;i<gapnum;++i)
//    {
//        int cur=getrandom(0,max(new_len-gaplength-1+i*(-new_len/2),0));
//
//        for(int i=0;i<gaplength;++i)
//        {
//            pos.insert(cur+i);
//        }
//    }
//    int cur=getrandom(0,new_len-remain-1);
//    for(int i=0;i<remain;++i)
//    {
//        pos.insert(cur+i);
//    }
    while(pos.size()<sub_len)
    {
        pos.insert(getrandom(0,new_len-1));
    }

    for(int i=0,j=0;i<new_len;++i)
    {
        if(pos.find(i)==pos.end())
        {
            new_str.push_back(str[j++]);
        }
        else
        {
            new_str.push_back('-');
            new_pos[i]=j;
        }
    }
    return {new_pos,new_str};
}

struct unit
{
    vector<string> strs;
    vector<string> pre_strs;
    vector<int> lens;
    vector<map<int,int>> pos;
    int max_len;
    int cost;
    unit(const vector<string>& outdata)
    {
        this->pre_strs=outdata;
        this->strs=outdata;
        for(auto& str:strs)
        {
            lens.push_back(str.size());
        }
        pos=vector<map<int,int>>(outdata.size());
        max_len=*max_element(lens.begin(),lens.end())*tuozhan_rate;
        for(int i=0;i<strs.size();++i)
        {
            auto tmp=tuozhan(strs[i],max_len);
            pos[i]=tmp.first;
            strs[i]=tmp.second;
        }
        upDateCost();
    }
    unit(const unit& that)=default;
    unit& operator=(const unit& that)=default;

    int GetCost() const
    {
        return cost;
    }

    void check(int idx) const
    {
        string tmp;
        for(int i=0;i<max_len;++i)
        {
           if(strs[idx][i]!='-')
           {
                tmp.push_back(strs[idx][i]);
           }
        }
        if(tmp!=this->pre_strs[idx])
        {
            cout<<"error"<<endl;
            cout<<tmp<<endl;
            cout<<pre_strs[idx]<<endl;
            cout<<strs[idx]<<endl;
            exit(0);
        }
    }

    int upDateCost()
    {
        cost=0;
        for(int i=0;i<strs.size();++i)
        {
            for(int j=i+1;j<strs.size();++j)
            {
                for(int k=0;k<max_len;++k)
                {
                    if(strs[i][k]=='-'&&strs[j][k]=='-')
                    {
                        continue;
                    }
                    else if(strs[i][k]=='-'||strs[j][k]=='-')
                    {
                        cost+=gapcost;
                    }
                    else if(strs[i][k]!=strs[j][k])
                    {
                        cost+=mismatchcost;
                    }
                }
            }
        }
        return cost;
    }

    void Cross(unit& that)
    {
        string& str1=this->strs[0];
        string& str2=that.strs[0];
        vector<pair<int,int>> can_swap;
        for(auto& key1:this->pos[0])
        {
            auto key2=that.pos[0].find(key1.first);
            if(key2!=that.pos[0].end()&&key1.second==key2->second)
            {
                can_swap.push_back({key1.first,key2->first});
            }
//            auto key3=that.pos[0].find(str1.size()-key1.first-1);
//            if(key3!=that.pos[0].end()&&key1.second==lens[0]-key3->second-1)
//            {
//                can_swap.push_back({key1.first,-key3->first});
//            }
        }
        if(can_swap.empty())
        {
            return ;
        }
        pair<int,int> swap_pair;
        if(can_swap.size()==1)
        {
            swap_pair=can_swap[0];
        }
        else
        {
            int idx=getrandom(0,can_swap.size()-1);
            if(idx<0||idx>=can_swap.size())
            {
                cout<<"error"<<endl;
                cout<<idx<<endl;
                cout<<can_swap.size()<<endl;
            }
            swap_pair=can_swap[idx];
        }
        if(swap_pair.second<0)
        {
            for(int i=0;i<swap_pair.first;++i)
            {
                swap(str1[i],str2[max_len-1-i]);
            }
        }
        else
        {
            for(int i=0;i<swap_pair.first;++i)
            {
                swap(str1[i],str2[i]);
            }
        }

        this->upDateCost();
        this->upDatePos(0);
        that.upDateCost();
        that.upDatePos(0);
    }

    void upDatePos(int idx)
    {
        check(idx);
        this->pos[idx].clear();
        for(int i=0,j=0;i<max_len;++i)
        {
            if(strs[idx][i]=='-')
            {
                this->pos[idx][i]=j;
            }
            else
            {
                ++j;
            }
        }
    }

    void Mutation()
    {

        int index=getrandom(0,strs.size()-1);
        auto it=pos[index].begin();
        advance(it,getrandom(0,pos[index].size()-1));
        int pos1=it->first;
        int pre_num=it->second;
        bool flag=false;
        while(!flag)
        {
            if(pre_num)
            {
                for(int i=pos1-1;i>=0;--i)
                {
                    if(strs[index][i]!='-')
                    {
                        swap(strs[index][i],strs[index][pos1]);
                        this->upDatePos(index);
                        flag=true;
                        break;
                    }
                }
            }
            if(flag) break;
            if(lens[index]-pre_num)
            {
                for(int i=pos1+1;i<max_len;++i)
                {
                    if(strs[index][i]!='-')
                    {
                        swap(strs[index][i],strs[index][pos1]);
                        flag=true;
                        break;
                    }
                }
            }
        }
        this->upDateCost();
        this->upDatePos(index);
    }

    bool operator<(const unit& that) const
    {
        return this->cost<that.cost;
    }

    friend ostream& operator<<(ostream& out,const unit& that)
    {
        out<<"cost: "<<that.cost<<endl;
        out<<"Query: "<<that.strs[0]<<endl;
        for(int i=1;i<that.strs.size();++i)
        {
            out<<"Database"<<i<<": "<<that.strs[i]<<endl;
        }
        return out;
    }

};

enum class QueryType
{
    Query2,
    Query3,
};

struct Group
{
    vector<unit> units;
    int gen;
    QueryType type;
    void logging()
    {
        ofstream out("D:\\MY_CODE\\CPP\\CS3317\\Project1\\result_"+to_string(type==QueryType::Query2?2:3)+".txt",ios::app);
        out<<"----------------------------------------"<<endl;
        out<<"////////////////////////////////////////"<<endl;
        auto time=chrono::system_clock::now();
        auto tt=chrono::system_clock::to_time_t(time);
        string timp=ctime(&tt);
        timp.pop_back();
        out<<"[Time: "<<timp<<"]"<<endl;
        out<<"[Args: ";
        out<<"TUOZHAN_RATE: "<<tuozhan_rate<<", ";
        out<<"CROSS_RATE: "<<pc<<", ";
        out<<"MUTATION_RATE: "<<pm<<", ";
        out<<"POPULATION_SIZE: "<<units.size()<<", ";
        out<<"GENERATION: "<<gen<<", ";
        out<<"]"<<endl;

        out<<"[Query: "<<units[0].pre_strs[0]<<"]"<<endl;

        int count=0;
        for(int j=0;j<units.size()&&count<5;++j)
        {
            if(j>=1&&units[j].pre_strs==units[j-1].pre_strs) continue;
            out<<units[j]<<endl;
            count++;
        }
    
        out<<"////////////////////////////////////////"<<endl;
        out<<"----------------------------------------"<<endl;
        out<<endl;
        out<<endl;
    }
    Group(const string& query,const vector<string>& databases,QueryType type,int gen)
    {
        this->type=type;
        this->gen=gen;
        if(type==QueryType::Query2)
        {
            for(auto& database:databases)
            {
                for(int i=0;i<10;++i)
                {
                    units.push_back(unit({query,database}));
                }
            }
        }
        else
        {
            cout<<databases.size()<<endl;
            for(int i=0;i<databases.size();++i)
            {
                for(int j=i+1;j< databases.size();++j)
                {
                    units.push_back(unit({query,databases[i],databases[j]}));
                }
            }
        }
    }

    double pm=0.1;
    double pc=0.95;
    double ps=0.05;

    void Evolution()
    {
        int N=units.size();
        int temp1=N*pc/2;
        int temp2=N*(1-pc);
        int temp3=N*(1-pc/2);
        int temp4=N*(1-ps);
        int temp5=N*ps;
        sort(units.begin(),units.end());
        for(int i=0;i<gen;++i)
        {
//            //Selection
//            for(int j=0;j<temp4;++j)
//            {
//                units[j+temp5]=units[j];
//            }
            //Cross
            for(int j=0;j<temp1-1;j+=2)
            {
                units[j+temp2].Cross(units[j+temp3]);
            }
            //Mutation
            for(int j=0;j<units.size()*pm;++j)
            {
                units[getrandom(0,N-1)].Mutation();
            }
            sort(units.begin(),units.end());
            if(i%100==0)
            {
                cout<<"Query: "<<units[0].pre_strs[0]<<" Generation: "<<i<<endl;
            }
            if(i==gen-1)
            {
                // ofstream out("D:\\MY_CODE\\CPP\\CS3317\\Project1\\result_2.txt",ios::app);
                // out<<"----------------------------------------"<<endl;

                // int count=0;
                // for(int j=0;j<units.size()&&count<5;++j)
                // {
                //     if(j>=1&&units[j].pre_strs==units[j-1].pre_strs) continue;
                //     out<<units[j]<<endl;
                //     count++;
                // }
                // out<<"----------------------------------------"<<endl;
                logging();
            }
        }

    }


};

int main()
{
    ifstream query_file("D:\\MY_CODE\\CPP\\CS3317\\Project1\\MSA_query.txt");
    ifstream database_file("D:\\MY_CODE\\CPP\\CS3317\\Project1\\MSA_database.txt");
    vector<string> querys_2,querys_3;
    vector<string> databases;
    string line;
    while (getline(query_file, line))
    {
        if(line.size() == 1)
        {
            continue;
        }
        if(querys_2.size()==5)
        {
            querys_3.push_back(line);
        }
        else querys_2.push_back(line);

    }
    while (getline(database_file, line))
    {
        databases.push_back(line);
    }
   for(auto& query:querys_2)
   {

       Group group(query,databases,QueryType::Query2,1000);
       group.Evolution();

   }
    for(auto& query:querys_3)
    {
        Group group(query,databases,QueryType::Query3,1000);
        group.Evolution();
    }
    return 0;
}

