#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<queue>
#include<set>
#include<unordered_set>
#include<algorithm>
#include<chrono>
#include<unordered_map>
#include<memory>
using namespace std;
int gapcost = 2;
int mismatchcost = 3;

namespace std
{
    template<>
    class hash<pair<string,string>>
    {
    public:
        size_t operator()(const pair<string,string>& p) const
        {
            return hash<string>()(p.first)^hash<string>()(p.second);
        }
    };
}
class Dp;
static unordered_map<pair<string,string>,shared_ptr<Dp>> caches;

class Dp:public enable_shared_from_this<Dp>
{
private:
    vector<vector<int>> dp;
public:
    static shared_ptr<Dp> getDp(const string& str1,const string& str2)
    {
        pair<string,string> p(str1,str2);
        if(caches.find(p)==caches.end())
        {
            caches[p]= make_shared<Dp>(str1,str2);
        }
        return caches[p];
    }
    Dp(const string& str1,const string& str2)
    {
        vector<string> strs={str1,str2};
        vector<int> lens;
        for(auto& str:strs)
        {
            lens.push_back(str.size());
        }
        dp=vector<vector<int>>(lens[0]+1,vector<int>(lens[1]+1,0));
        for(int xy=dp.size()+dp[0].size()-3;xy>-1;--xy)
        {
            for( int x=max(0,xy-lens[1]);x<min(xy+1,(int)dp.size());++x)
            {
                int y=xy-x;
                vector<int> tmp(3,INT_MAX);
                if(x<lens[0])
                {
                    tmp[0]=dp[x+1][y]+gapcost;
                }
                if(y<lens[1])
                {
                    tmp[1]=dp[x][y+1]+gapcost;
                }
                if(x<lens[0]&&y<lens[1])
                {
                    tmp[2]=dp[x+1][y+1]+(strs[0][x]==strs[1][y]?0:mismatchcost);
                }
                dp[x][y]=*min_element(tmp.begin(),tmp.end());
            }
        }
    }
    Dp(const Dp& dp)=default;
    const vector<int>& operator [](int pos) const
    {
        return dp[pos];
    }
};


struct Node
{
    shared_ptr<Node> parent;
    vector<int> pos;
    int g;
    int h;
    int f;
    int heuristic(const vector<shared_ptr<Dp>>& dps)
    {
        int res=0;
        for(int i=0;i<pos.size();++i)
        {
            for(int j=i+1;j<pos.size();++j)
            {
                res+=(*dps[i+j-1])[pos[i]][pos[j]];
            }
        }
        return res;
    }
    Node(const vector<int>& pos, int g,shared_ptr<Node> parent=nullptr,const vector<shared_ptr<Dp>>& dps={}):pos(pos),g(g),parent(parent)
    {
        h = heuristic(dps);
        f = g+h;
    }
    Node(const Node& node)=default;
//    bool operator==(const Node& rhs) const
//    {
//        return pos == rhs.pos;
//    }
//    bool operator<(const Node& rhs) const
//    {
//        return f < rhs.f;
//    }
};



struct NodeCompare
{
    bool operator()(const shared_ptr<Node> lhs, const shared_ptr<Node> rhs)
    {
        return lhs->f > rhs->f;
    }
};



class AStar
{
private:
    shared_ptr<Node> start;
    shared_ptr<Node> goal;
    vector<vector<vector<bool>>> visited;
    priority_queue<shared_ptr<Node>,vector<shared_ptr<Node>>,NodeCompare> open_list;
    vector<string> strs;
    vector<int> lens;
    vector<shared_ptr<Dp>> dps;
    int cost=-1;
    shared_ptr<Node> dstnode=nullptr;
public:
    AStar(const string& query,const string& database1,const string& database2)
    {
        strs={query,database1,database2};
        for(auto& str:strs)
        {
            lens.push_back(str.size());
        }
        dps={Dp::getDp(strs[0],strs[1]),Dp::getDp(strs[0],strs[2]),Dp::getDp(strs[1],strs[2])};
        visited=vector<vector<vector<bool>>>(lens[0]+1,vector<vector<bool>>(lens[1]+1,vector<bool>(lens[2]+1,false)));
        this->goal=make_shared<Node>(vector<int>({lens[0],lens[1],lens[2]}),0,nullptr,dps);

        this->start = make_shared<Node>(vector<int>({0,0,0}),0,nullptr,dps);
        open_list.push(start);

    }
    ~AStar()
    {
    }

    void solve()
    {
        while(!open_list.empty())
        {
            shared_ptr<Node> current = open_list.top();
            open_list.pop();
            if(current->pos == goal->pos)
            {
                dstnode = current;
                cost= current->f;
//                if(cost==0)
//                {
//                    while(dstnode)
//                    {
//                        cout<<dstnode->pos[0]<<" "<<dstnode->pos[1]<<" "<<dstnode->pos[2]<<" "<<dstnode->f<<" "<<dstnode->g<<" "<<dstnode->h<<endl;
//                        dstnode = dstnode->parent;
//                    }
//                    system("pause");
//                }
                return;
            }
//            cout<<current->pos[0]<<" "<<current->pos[1]<<" "<<current->pos[2]<<" "<<current->f<<endl;
            if(visited[current->pos[0]][current->pos[1]][current->pos[2]])
            {
                continue;
            }
            visited[current->pos[0]][current->pos[1]][current->pos[2]]=true;
            for(int i=0;i<3;++i)
            {
                if(current->pos[i] < lens[i])
                {
                    vector<int> new_pos = current->pos;
                    new_pos[i]++;
                    shared_ptr<Node> new_node = make_shared<Node>(new_pos,current->g+2*gapcost,current,dps);
                    open_list.push(new_node);
                }
            }
            for(int i=0;i<3;++i)
            {
                if(current->pos[i] < lens[i])
                {
                    for(int j=i+1;j<3;++j)
                    {
                        if(current->pos[j] < lens[j])
                        {
                            if(i==0&& j==1&&current->pos[i] ==4&& current->pos[j]==4)
                            {
                                int a=0;
                            }
                            vector<int> new_pos = current->pos;
                            new_pos[i]++;
                            new_pos[j]++;
                            int new_g=current->g+2*gapcost+(strs[i][current->pos[i]]==strs[j][current->pos[j]]?0:mismatchcost);
                            shared_ptr<Node> new_node = make_shared<Node>(new_pos,new_g,current,dps);
                            open_list.push(new_node);
                        }
                    }
                }
            }
            bool flag=true;
            for(int i=0;i<3;++i) {
                if (current->pos[i] >= lens[i]) {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                vector<int> new_pos = current->pos;
                for(int i=0;i<3;++i)
                {
                    new_pos[i]++;
                }
                int misnums=0;
                for(int i=0;i<3;++i)
                {
                    for(int j=i+1;j<3;++j)
                    {
                        if(strs[i][current->pos[i]]!=strs[j][current->pos[j]])
                        {
                            misnums++;
                        }
                    }
                }
                int new_g=current->g+misnums*mismatchcost;
                shared_ptr<Node> new_node = make_shared<Node>(new_pos,new_g,current,dps);
                open_list.push(new_node);
            }
        }
    }

    pair<int,tuple<string,string,string>> get_result()
    {
        if(!dstnode)
        {
            solve();
        }
        vector<string> res(3);
        shared_ptr<Node> tmp = dstnode;
        while(tmp->parent)
        {
            for(int i=0;i<3;++i)
            {
                if(tmp->pos[i] != tmp->parent->pos[i])
                {
                    res[i].push_back(strs[i][tmp->pos[i]-1]);
                }
                else
                {
                    res[i].push_back('-');
                }
            }
            tmp = tmp->parent;
        }
        for(auto& str:res)
        {
            reverse(str.begin(),str.end());
        }
        return {cost,{res[0],res[1],res[2]}};
    }

};




static pair<int,tuple<string,string,string>> solve_3(const string& query,const vector<string>& databases)
{
    priority_queue<pair<int,tuple<string,string,string>>,vector<pair<int,tuple<string,string,string>>>,greater<pair<int,tuple<string,string,string>>>> results;
    for(int i=0;i<databases.size();++i)
    {
        for(int j=i+1;j<databases.size();++j) {
            AStar astar(query, databases[i], databases[j]);
            results.push(astar.get_result());
            if(results.size()%500==0)
            {
                cout<<"TO "<<results.size()<<"nums"<<endl;
            }
        }
    }
    auto res=results.top();
    ofstream out("D:\\MY_CODE\\CPP\\CS3317\\Project1\\True_Result_3.txt",ios::app);
    int num=5;
    while(!results.empty() && num--)
    {
        auto res=results.top();
        string tmp1,tmp2;
        auto str1=get<1>(res.second);
        auto str2=get<2>(res.second);
        for(char ch:str1)
        {
            if(ch!='-')
            {
                tmp1.push_back(ch);
            }
        }
        for(char ch:str2)
        {
            if(ch!='-')
            {
                tmp2.push_back(ch);
            }
        }
        out<<query<<" "<<tmp1<<" "<<tmp2<<endl;
        results.pop();
    }

    
    return res;
}


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

    for(auto& query : querys_3)
    {
        auto start = chrono::steady_clock::now();
        auto result = solve_3(query, databases);
        auto end = chrono::steady_clock::now();
        cout<<"Time: "<<chrono::duration_cast<chrono::milliseconds>(end-start).count()<<"ms"<<endl;
//        cout<<"Query: "<<query<<endl;
        cout<<"Cost: "<<result.first<<endl;
//        cout<<"Alignment: "<<endl;
//        cout<<get<0>(result.second)<<endl;
//        cout<<get<1>(result.second)<<endl;
//        cout<<get<2>(result.second)<<endl;
    }

    return 0;
}