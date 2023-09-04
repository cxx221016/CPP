#include<cmath>
#include<algorithm>
#include<stack>
#include<vector>
#include<iostream>
using namespace std;
template<typename T>
class KdTree
{
    //定义节点结构
    //----------
    struct kdNode
    {
        vector<T> vec;
        int splitAttribute;
        kdNode *lChild;
        kdNode *rChild;
        kdNode *parent;

        kdNode(vector<T> v = {}, int split = 0, kdNode *lCh = nullptr,
            kdNode *rCh = nullptr, kdNode *par = nullptr) :vec(v), splitAttribute(split),
            lChild(lCh), rChild(rCh), parent(par) {}
    };

public:
    KdTree()
    {
        root = nullptr;
    }

    kdNode *getRoot()
    {
        return root;
    }

    vector<T> getRootData()
    {
        return root->vec;
    }
    //嵌套型数据结构
    //------------
    KdTree(vector<vector<T>> &data)
    {
        root = createKdTree(data);
    }

    //转置矩阵
    //-------
    vector<vector<T>> transpose(vector<vector<T>> &data)
    {

        int m = data.size();
        int n = data[0].size();
        vector<vector<T>> trans(n, vector<T>(m, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                trans[i][j] = data[j][i];
            }
        }
        return trans;
    }

    //计算每个方向上的方差
    //-----------------
    double getVariance(vector<T> &vec)
    {
        int n = vec.size();
        double sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += vec[i];
        }
        double avg = sum / n;
        sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += pow(vec[i] - avg, 2);//#include<cmath>
        }
        return sum / n;
    }

    //根据最大方差确定垂直于超平面的轴序号split attribute
    //-----------------------------------------
    int getSplitAttribute(vector<vector<T>> &data)
    {
        int size = data.size();
        int splitAttribute = 0;
        double maxVar = getVariance(data[0]);
        for (int i = 1; i < size; i++)
        {
            double temp = getVariance(data[i]);
            if (temp > maxVar)
            {
                splitAttribute = i;
                maxVar = temp;
            }
        }
        return splitAttribute;
    }

    //查询中值
    //-------
    T getSplitValue(vector<T> &vec)
    {
        sort(vec.begin(), vec.end());
        return vec[vec.size() / 2];
    }

    //计算2个k维点的距离
    //---------------
    static double getDistance(vector<T> &v1, vector<T> &v2)
    {
        double sum = 0;
        for (size_t i = 0; i < v1.size(); i++)
        {
            sum += pow(v1[i] - v2[i], 2);
        }
        return sqrt(sum);
    }

    //创建kd-tree
    //-----------
    kdNode *createKdTree(vector<vector<T>> &data)
    {
        //cout << "create_1" << endl;
        if (data.empty())
            return nullptr;

        int n = data.size();
        if (n == 1)
        {
            return new kdNode(data[0], -1);
        }

        //获得轴序号与值
        //------------
        vector<vector<T>> data_T = transpose(data);
        int splitAttribute = getSplitAttribute(data_T);
        int splitValue = getSplitValue(data_T[splitAttribute]);

        //分割数据空间：根据attribute和value
        //------------------------------
        vector<vector<T>> left;
        vector<vector<T>> right;

        int flag = 0;
        kdNode *splitNode = nullptr;
        for (int i = 0; i < n; i++)
        {
            if (flag == 0 && data[i][splitAttribute] == splitValue)
            {
                splitNode = new kdNode(data[i]);
                splitNode->splitAttribute = splitAttribute;
                flag = 1;
                continue;
            }
            if (data[i][splitAttribute] <= splitValue)
            {
                left.push_back(data[i]);
            }
            else
            {
                right.push_back(data[i]);
            }
        }

        splitNode->lChild = createKdTree(left);
        splitNode->rChild = createKdTree(right);
        return splitNode;
    }

    //-----------------------------最邻近算法------------------------------------
    //-------------------------------------------------------------------------

    //指定起点查询
    //----------
    vector<T> searchNearestNeighbor(vector<T> &target, kdNode *start)
    {
        vector<T> NN = { 0,0 };//给定一个初始值
        stack<kdNode *> searchPath;
        kdNode *p = start;
         
        if (p != nullptr)
        {
            while (p->splitAttribute != -1) //-1是指已到达边缘点，没有分割属性
            {
                searchPath.push(p);
                int splitAttribute = p->splitAttribute;
                if (target[splitAttribute] <= p->vec[splitAttribute])
                {
                    p = p->lChild;
                }
                else
                {
                    p = p->rChild;
                }
            }
            NN = p->vec;
        }

        double mindist = KdTree::getDistance(target, NN);
        kdNode *curNode;
        double dist;
        vector<T> nn;
        while (!searchPath.empty())
        {
            curNode = searchPath.top();
            searchPath.pop();
            dist = KdTree::getDistance(target, curNode->vec);

            if (dist < mindist)
            {
                mindist = dist;
                NN = curNode->vec;

                //判断以target为中心，以dist为半径的球是否和节点的超平面相交
                if (curNode->vec[curNode->splitAttribute] >= target[curNode->splitAttribute] - dist
                    && curNode->vec[curNode->splitAttribute] <= target[curNode->splitAttribute] + dist)
                {
                    if (target[curNode->splitAttribute] > curNode->vec[curNode->splitAttribute])
                    {
                        nn = searchNearestNeighbor(target, curNode->lChild);
                    }
                    else
                    {
                        nn = searchNearestNeighbor(target, curNode->rChild);
                    }

                    if (KdTree::getDistance(target, nn) < KdTree::getDistance(target, NN))
                    {
                        NN = nn;
                    }
                }
            }
            else
            {
                if (curNode->vec[curNode->splitAttribute] >= target[curNode->splitAttribute] - mindist
                    && curNode->vec[curNode->splitAttribute] <= target[curNode->splitAttribute] + mindist)
                {
                    if (target[curNode->splitAttribute] > curNode->vec[curNode->splitAttribute])
                    {
                        nn = searchNearestNeighbor(target, curNode->lChild);
                    }
                    else
                    {
                        nn = searchNearestNeighbor(target, curNode->rChild);
                    }

                    if (KdTree::getDistance(target, nn) < KdTree::getDistance(target, NN))
                    {
                        NN = nn;
                    }
                }
            }
        }
        return NN;
    }

    //从根节点进行查询
    //-------------
    vector<T> searchNearestNeighbor(vector<T> &target)
    {
        vector<T> NN;
        NN = searchNearestNeighbor(target, root);
        return NN;
    }

    //打印kdTree
    //----------
    void printTree(kdNode *root)
    {
        cout << "[";
        if (root->lChild)
        {
            cout << "left:";
            printTree(root->lChild);
        }

        if (root)
        {
            cout << "(";
            for (size_t i = 0; i < root->vec.size(); i++)
            {
                cout << root->vec[i];
                if (i != (root->vec.size() - 1))
                    cout << ",";
            }
            cout << ")";
        }

        if (root->rChild)
        {
            cout << "right";
            printTree(root->rChild);
        }
        cout << "]";
    }

private:
    kdNode * root;
};

int main()
{
    double data[7][2] = { { 2,3 },{ 5,4 },{ 9,6 },{ 4,7 },{ 8,1 },{ 7,2 },{9,3}};
    vector<vector<double>> train(7, vector<double>(2, 0));
    for (unsigned int i = 0; i < 7; i++)
    {
        for (unsigned int j = 0; j < 2; j++)
        {
            train[i][j] = data[i][j];
        }
    }
    KdTree<double> *Tree = new KdTree<double>(train);  

    //输出整棵树
    Tree->printTree(Tree->getRoot());
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
    vector<double> nearestNeighbor = Tree->searchNearestNeighbor(goal);
    vector<double>::iterator beg = nearestNeighbor.begin();
    cout << endl;
    cout << "(" << i << "," << j << ") nearest neighbor is: ";
    while (beg != nearestNeighbor.end())
        cout << *beg++ << ",";
    cout << endl;
    system("pause");
    return 0;
}
