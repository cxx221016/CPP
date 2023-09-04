#include<cmath>
#include<algorithm>
#include<vector>
#include<stack>
#include<numeric>
#include<sstream>
#include<iostream>

using namespace std;

template<typename T>
struct kdNode
{
    vector<T> vec;
    int splitAttribute;
    kdNode *left;
    kdNode *right;
    kdNode *parent;

    kdNode(vector<T> v={},int split=0,kdNode* l=nullptr,kdNode* r=nullptr,kdNode* p=nullptr):vec(v),splitAttribute(split),left(l),right(r),parent(p){}
};

template<typename T>
class KdTree
{
private:
    kdNode<T>* root;
public:
    KdTree()
    {
        root=nullptr;
    }
    KdTree(const vector<vector<T>>& data)
    {
        root=build(data);
    }

    vector<T> getRootData()
    {
        return root->vec;
    }
    kdNode<T>* build(const vector<vector<T>>& data);
    vector<vector<T>> trans(const vector<vector<T>>& data);
    double getVariance(const vector<T>& vec);
    int getsplitAttribute(const vector<vector<T>>& data);
    int getsplitValue(vector<T>& vec);
    static double getDistance(const vector<T>& v1,const vector<T>& v2);
    vector<T> search(vector<T>& target,kdNode<T>* root);
    vector<T> search(vector<T>& target);
    
    friend istream& operator>>(istream& in,KdTree<T>& Tree)
    {
        int dim;
        cin>>dim;
        vector<vector<T>> data;
        vector<T> tmps(dim);
        while(in)
        {
            for(auto& tmp:tmps)
            {
                in>>tmp;
            }
            data.push_back(tmps);
        }
        data.pop_back();
        Tree =KdTree<T> (data);
        return in;
    }
    friend istream& operator>>(istream& in,KdTree<T>*& Tree)
    {
        int dim;
        cin>>dim;
        vector<vector<T>> data;
        vector<T> tmps(dim);
        while(in)
        {
            for(auto& tmp:tmps)
            {
                in>>tmp;
            }
            data.push_back(tmps);
        }
        data.pop_back();
        Tree =new KdTree<T> (data);
        return in;
    }
    friend ostream& operator<<(ostream& out,KdTree& Tree)
    {
        Tree.printTree(Tree.root,out);
        return out;
    }

    friend ostream& operator<<(ostream& out,KdTree*& Tree)
    {
        Tree->printTree(Tree->root,out);
        return out;
    }

    void printTree(kdNode<T>* root,ostream& out);
};

template<typename T>
kdNode<T>* KdTree<T>::build(const vector<vector<T>>& data)
{ 
    if(data.empty()) return nullptr;
    int n=data.size();
    if(n==1) return new kdNode<T>(data[0],-1);
    vector<vector<T>> data_T=trans(data);
    int splitAttribute=getsplitAttribute(data_T);
    int splitValue=getsplitValue(data_T[splitAttribute]);

    int flag=false;
    vector<vector<T>> left;
    vector<vector<T>> right;
    kdNode<T>* splitNode=nullptr;
    for(int i=0;i<n;++i)
    {
        if(!flag&&data[i][splitAttribute]==splitValue)
        {
            splitNode=new kdNode<T>(data[i]);
            splitNode->splitAttribute=splitAttribute;
            flag=true;
            continue;
        }
        if(data[i][splitAttribute]<=splitValue)
        {
            left.push_back(data[i]);
        }
        else
        {
            right.push_back(data[i]);
        }
    }
    splitNode->left=build(left);
    splitNode->right=build(right);
    return splitNode;
}

template<typename T>
vector<vector<T>> KdTree<T>::trans(const vector<vector<T>>& data)
{
    int m=data.size();
    int n=data[0].size();
    vector<vector<T>> data_T(n,vector<T>(m));

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            data_T[i][j]=data[j][i];
        }
    }
    return data_T;
}

template<typename T>
double KdTree<T>::getVariance(const vector<T>& vec)
{
    int n=vec.size();
    double sum=accumulate(vec.begin(),vec.end(),0.0);
    double avg=sum/n;

    double res=0;
    for_each(vec.begin(),vec.end(),[&](const T& t)
    {
        res+=pow(t-avg,2);
    });

    return res/n;
}

template<typename T>
int KdTree<T>::getsplitAttribute(const vector<vector<T>>& data)
{
    vector<pair<double,int>> to_sort;
    for(int i=0;i<data.size();++i)
    {
        to_sort.emplace_back(getVariance(data[i]),i);
    }

    sort(to_sort.begin(),to_sort.end());
    return to_sort.back().second;
}

template<typename T>
int KdTree<T>::getsplitValue(vector<T>& vec)
{
    sort(vec.begin(),vec.end());
    return vec[vec.size()/2];
}

template<typename T>
double KdTree<T>::getDistance(const vector<T>& v1,const vector<T>& v2)
{
    double res=0;
    for(int i=0;i<v1.size();++i)
    {
        res+=pow(v1[i]-v2[i],2);
    }
    return sqrt(res);
}

template<typename T>
vector<T> KdTree<T>::search(vector<T>& target,kdNode<T>* root)
{
    vector<T> NN={0,0};
    stack<kdNode<T>*> stk;
    kdNode<T>* p=root;

    if(p)
    {
        while(p->splitAttribute!=-1)
        {
            stk.push(p);
            int splitAttribute=p->splitAttribute;
            if(target[splitAttribute]<=p->vec[splitAttribute])
            {
                p=p->left;
            }
            else
            {
                p=p->right;
            }
        }
        NN=p->vec;
    }

    double mindis=KdTree::getDistance(target,NN);
    kdNode<T> *curNode;
    double dis;
    vector<T> nn;
    while(!stk.empty())
    {
        curNode=stk.top();
        stk.pop();
        dis=KdTree::getDistance(target,curNode->vec);
        if(dis<mindis)
        {
            mindis=dis;
            NN=curNode->vec;
            if(curNode->vec[curNode->splitAttribute]>=target[curNode->splitAttribute]-dis&&curNode->vec[curNode->splitAttribute]<=target[curNode->splitAttribute]+dis)
            {
                if(target[curNode->splitAttribute]>curNode->vec[curNode->splitAttribute])
                {
                    nn=search(target,curNode->left);
                }
                else
                {
                    nn=search(target,curNode->right);
                }

                if(KdTree::getDistance(target,nn)<KdTree::getDistance(target,NN))
                {
                    NN=nn;
                }
            }
        }

        else
        {
            if(curNode->vec[curNode->splitAttribute]>=target[curNode->splitAttribute]-mindis&&curNode->vec[curNode->splitAttribute]<=target[curNode->splitAttribute]+mindis)
            {
                if(target[curNode->splitAttribute]>curNode->vec[curNode->splitAttribute])
                {
                    nn=search(target,curNode->left);
                }
                else
                {
                    nn=search(target,curNode->right);
                }

                if(KdTree::getDistance(target,nn)<KdTree::getDistance(target,NN))
                {
                    NN=nn;
                }
            }
        }
    }
    return NN;
}

template<typename T>
vector<T> KdTree<T>::search(vector<T>& target)
{
    return search(target,root);
}

template<typename T>
void KdTree<T>::printTree(kdNode<T>* root,ostream& out)
    {
        out << "[";
        if (root->left)
        {
            out << "left:";
            printTree(root->left,out);
        }

        if (root)
        {
            out << "(";
            for (size_t i = 0; i < root->vec.size(); i++)
            {
                out << root->vec[i];
                if (i != (root->vec.size() - 1))
                    out << ",";
            }
            out << ")";
        }

        if (root->right)
        {
            out << "right";
            printTree(root->right,out);
        }
        out << "]";
    }

int main()
{
    /*
    2
    2 3
    5 4
    9 6
    4 7
    8 1
    7 2
    9 2

    */
    /*double data[7][2] = { { 2,3 },{ 5,4 },{ 9,6 },{ 4,7 },{ 8,1 },{ 7,2 },{9,2} };
    vector<vector<double>> train(7, vector<double>(2, 0));
    for (unsigned int i = 0; i < 7; i++)
    {
        for (unsigned int j = 0; j < 2; j++)
        {
            train[i][j] = data[i][j];
        }
    }
    KdTree<double> *Tree = new KdTree<double>(train);  
    */
    //输出整棵树
    KdTree<double> *Tree;
    cin>>Tree;
    cout<<Tree;
    cout << endl;
    cout << endl;


    //输出根节点
    vector<double> root = Tree->getRootData();
    vector<double>::iterator r = root.begin();
    cout << "root=";
    while (r != root.end())
        cout << *r++ << ",";

    //查找最近点
    cout << endl;
    cout << endl;
    vector<double> goal;
    double i, j;
    i = 9.0;
    j = 4.0;
    goal.push_back(i);
    goal.push_back(j);
    vector<double> nearestNeighbor = Tree->search(goal);
    vector<double>::iterator beg = nearestNeighbor.begin();
    cout << endl;
    cout << "(" << i << "," << j << ") nearest neighbor is: ";
    while (beg != nearestNeighbor.end())
        cout << *beg++ << ",";
    cout << endl;
    system("pause");
    return 0;
}