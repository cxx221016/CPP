#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
using namespace std;

namespace std {
template<>
class hash<pair<int,int>> 
{
public:
    size_t operator()(const pair<int,int> &p) const {
        return hash<int>()(p.first)^hash<int>()(p.second);
    }
};
};

template<class T>
struct HuffmanNode
{
    T val;
    int weight;
    int left;
    int right;
    int parent;
    HuffmanNode(int _weight=0,int _left=0,int _right=0,int _parent=0):weight(_weight),left(_left),right(_right),parent(_parent){}
    HuffmanNode(T _val,int _weight=0,int _left=0,int _right=0,int _parent=0):val(_val),weight(_weight),left(_left),right(_right),parent(_parent)
    {

    }
    HuffmanNode(const HuffmanNode& other)
    {
        val=other.val;
        weight=other.weight;
        left=other.left;
        right=other.right;
        parent=other.parent;
    }

    friend ostream& operator<<(ostream& out,HuffmanNode<T>& Node)
    {
        out<<Node.val<<" "<<Node.weight<<" "<<Node.left<<" "<<Node.right<<" "<<Node.parent<<endl;
        return out;
    }

    friend istream& operator>>(istream& in,HuffmanNode<T>& Node)
    {
        in>>Node.val>>Node.weight>>Node.left>>Node.right>>Node.parent;
        return in;
    }
};

template<class T>
class HuffmanTree
{
private:
    vector<HuffmanNode<T>> BBtree;
    map<T,string> HFCode;
public:
    HuffmanTree(){};
    HuffmanTree(const HuffmanTree& other);
    HuffmanTree(const map<T,int>& mp);
    map<T,string> HuffmanCode();
    friend ostream& operator<<(ostream& out,HuffmanTree<T>& tree)
    {
        for(auto& entry:tree.HFCode)
        {
            out<<endl<<entry.first<<" "<<entry.second;
        }
        return out;
    }
    friend istream& operator>>(istream& in,HuffmanTree<T>& tree)
    {
        T ch;
        int n;
        map<T,int> mp;
        while(in)
        {
            in>>ch>>n;
            mp[ch]=n;
        }
        tree=HuffmanTree<T> (mp);
        return in;
    }
};

template<class T>
HuffmanTree<T>::HuffmanTree(const HuffmanTree& other)
{
    BBtree=other.BBtree;
}


template<class T>
HuffmanTree<T>::HuffmanTree(const map<T,int>& mp)
{
    unordered_map<pair<int,int>,string> to_cmp;
    auto cmp=[&](const pair<int,int>&a ,const pair<int,int>& b)
    {
        return a.first==b.first? to_cmp[a]>to_cmp[b] : a.first>b.first;
    };
    priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> que(cmp);
    int n=mp.size();
    int m=2*n;
    BBtree.resize(m);
    int index=n;
    for(auto& entry:mp)
    {
        to_cmp[{entry.second,index}]=entry.first;
        que.emplace(entry.second,index);
        BBtree[index++]=HuffmanNode<T> (entry.first,entry.second,0,0,0);
    }
    index=n-1;
    while(index)
    {
        string fir=to_cmp[que.top()];
        int firstmin=que.top().second;que.pop();
        string sec=to_cmp[que.top()];
        int secondmin=que.top().second;que.pop();

        BBtree[firstmin].parent=BBtree[secondmin].parent=index;
        BBtree[index].weight=BBtree[firstmin].weight+BBtree[secondmin].weight;
        BBtree[index].left=firstmin;
        BBtree[index].right=secondmin;
        to_cmp[{BBtree[index].weight,index}]=fir+sec;
        que.emplace(BBtree[index].weight,index);
        index--;
    }
}


template<class T>
map<T,string> HuffmanTree<T>::HuffmanCode()
{
    //unordered_map<T,string> HFCode;
    int m=BBtree.size();
    int n=m>>1;
    if(n==0) return HFCode;
    if(n==1) {HFCode[BBtree[1].val]="0"; return HFCode;}
    stack<pair<int,string>> stk;
    stk.emplace(1,string());
    while(!stk.empty())
    {
        int i=stk.top().first;
        string str=stk.top().second;
        stk.pop();
        if(BBtree[i].right==0&&BBtree[i].left==0) { HFCode[BBtree[i].val]=str;}
        if(BBtree[i].right!=0) stk.emplace(BBtree[i].right,str+"1");
        if(BBtree[i].left!=0) stk.emplace(BBtree[i].left,str+"0");
    }
    return HFCode;
}

//定义main函数
int main()
{
    /********** Begin **********/
    //读取测试输入
    char ch;
    string input;
    while((ch=cin.get())!=EOF) {input.push_back(ch);}
    input.pop_back();
    map<char,int> mp;

    map<char,string> change;
    for(auto& in:input)
    {
        mp[in]++;
    }

    HuffmanTree<char> tree(mp);
    change=tree.HuffmanCode();
    ostringstream os;
    int res=0;
    for(auto& entry: change)
    {
        res+=mp[entry.first]*entry.second.size();
    }
    os<<res;
    os<<tree;
    string output=os.str();
    cout<<input.size()<<":"<<output.size()<<endl;;
    cout<<output;

    //请打印输出运算结果


	/********** End **********/
    system("pause");
  	return 0;
}
