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
#include<memory>
using namespace std;



struct Node
{
    shared_ptr<Node> parent;
    pair<int,int> pos;
    int g;
    int h;
    int f;
    int heuristic(shared_ptr<Node> goal)
    {
        if(!goal)
        {
            return 0;
        }
        return 3*abs(pos.first-goal->pos.first-(pos.second-goal->pos.second));
    }
    Node( pair<int,int> pos, int g,shared_ptr<Node> parent=nullptr,shared_ptr<Node> goal=nullptr):pos(pos),g(g),parent(parent)
    {
        h = heuristic(goal);
        f = g+h;
    }
    bool operator==(const Node& rhs)
    {
        return pos == rhs.pos;
    }
    bool operator<(const Node& rhs)
    {
        return f < rhs.f;
    }
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
    int gapcost = 3;
    int mismatchcost = 5;
    shared_ptr<Node> start;
    shared_ptr<Node> goal;
    vector<vector<int>> visited;
    priority_queue<shared_ptr<Node>,vector<shared_ptr<Node>>,NodeCompare> open_list;
    vector<pair<int,int>> directions = {{0,1},{1,1},{1,0}};
    string query, database;
    int len1,len2;
    int cost=-1;
    shared_ptr<Node> dstnode=nullptr;
public:
    AStar(const string& query,const string& database):query(query),database(database)
    {
        len1=query.size();
        len2=database.size();
        visited = vector<vector<int>>(query.size()+1,vector<int>(database.size()+1,0));

        this->goal=make_shared<Node>(Node({query.size(),database.size()},0));

        this->start = make_shared<Node>(Node({0,0},0,nullptr,goal));
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
                return;
            }
            if(visited[current->pos.first][current->pos.second] == 1)
            {
                continue;
            }
            visited[current->pos.first][current->pos.second] = 1;
            if (current->pos.first<len1)
            {

                auto next=make_shared<Node>(Node({current->pos.first+1,current->pos.second},current->g+gapcost,current,goal));
                open_list.push(next);
            }
            if (current->pos.second<len2)
            {
                auto next = make_shared<Node>(Node({current->pos.first,current->pos.second+1},current->g+gapcost,current,goal));
                open_list.push(next);
            }
            if (current->pos.first<len1 && current->pos.second<len2)
            {
                auto next = make_shared<Node>(Node({current->pos.first+1,current->pos.second+1},current->g+(query[current->pos.first]==database[current->pos.second]?0:mismatchcost),current,goal));
                open_list.push(next);
            }
        }
    }

    pair<int,pair<string,string>> get_result()
    {
        if(!dstnode)
        {
            solve();
        }
        string str1,str2;
        shared_ptr<Node> current = dstnode;
        while(current->parent)
        {
            if(current->pos.first == current->parent->pos.first)
            {
                str1.push_back('-');
                str2.push_back(database[current->pos.second-1]);
            }
            else if(current->pos.second == current->parent->pos.second)
            {
                str1.push_back(query[current->pos.first-1]);
                str2.push_back('-');
            }
            else
            {
                str1.push_back(query[current->pos.first-1]);
                str2.push_back(database[current->pos.second-1]);
            }
            current = current->parent;
        }
        reverse(str1.begin(),str1.end());
        reverse(str2.begin(),str2.end());

        return make_pair(cost,make_pair(str1,str2));
    }

};



static pair<int,pair<string,string>> solve(const string& query, const vector<string>& databases)
{
    priority_queue<pair<int,pair<string,string>>,vector<pair<int,pair<string,string>>>,greater<pair<int,pair<string,string>>>> results;
    for(auto& database : databases)
    {
        AStar astar(query,database);
        results.push(astar.get_result());
    }
    auto res=results.top();
    ofstream out("D:\\MY_CODE\\CPP\\CS3317\\Project1\\True_Result_2.txt",ios::app);
    int num=5;
    while(!results.empty() && num--)
    {
        auto res=results.top();
        string tmp;
        for(char ch:res.second.second)
        {
            if(ch!='-')
            {
                tmp.push_back(ch);
            }
        }
        out<<query<<" "<<tmp<<endl;
        results.pop();
    }

    
    return res;
}


int main()
{
    ifstream query_file("D:\\MY_CODE\\CPP\\CS3317\\Project1\\query_2.txt");
    ifstream database_file("D:\\MY_CODE\\CPP\\CS3317\\Project1\\MSA_database.txt");
    vector<string> querys;
    vector<string> databases;
    string line;
    while (getline(query_file, line))
    {
        querys.push_back(line);
    }
    while (getline(database_file, line))
    {
        databases.push_back(line);
    }
    for(auto& query : querys)
    {
        auto start = chrono::steady_clock::now();
        auto result = solve(query,databases);
        auto end = chrono::steady_clock::now();
        cout<<"Time: "<<chrono::duration_cast<chrono::milliseconds>(end-start).count()<<"ms"<<endl;
       cout<<"Query: "<<query<<endl;
        cout<<"Cost: "<<result.first<<endl;
       cout<<"Alignment: "<<endl;
       cout<<result.second.first<<endl;
       cout<<result.second.second<<endl;
    }
    system("pause");
    return 0;
}