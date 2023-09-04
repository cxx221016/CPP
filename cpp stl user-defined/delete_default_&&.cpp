#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;

struct Node
{
    char val;
    int weight;

    Node()=default;
    Node(char _val,int _weight):val(_val),weight(_weight){}
    Node(Node&& )=default;
    Node(const Node&)=default;
};

class MOVE
{
private:
    int val;
    Node t;
public:
    MOVE()=default;
    MOVE(int _val,Node _t):val(_val),t(_t){}
    MOVE(const MOVE&)=default;
    MOVE(MOVE&& )=default;

    friend ostream& operator<<(ostream& out,const MOVE& move)
    {
        out<<move.val<<" "<<move.t.val<<" "<<move.t.weight<<endl;
        return out;
    }
};

class Sort
{
private:
    vector<int> data;
public:
    Sort(const vector<int>& _data):data(_data){}
    Sort()=default;
    Sort(const Sort&)=default;
    Sort(Sort&&)=default;
    Sort sorted()&&
    {
        cout<<"&&"<<endl;
        sort(data.begin(),data.end());
        return *this;
    }
    Sort sorted() const &
    {
        cout<<"&"<<endl;
        Sort clone (*this);
        sort(clone.data.begin(),clone.data.end());
        return clone;
    }
};




int main()
{
    Node tmp('c',18);
    MOVE move(1,tmp);
    MOVE newmove(move);
    cout<<move<<newmove<<endl;
    vector<int> data{1,3,5,4,2};
    Sort temp1(data);
    temp1.sorted();
    std::move(temp1).sorted();
    system("pause");
    return 0;
}