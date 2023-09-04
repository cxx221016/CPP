#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include <numeric>
#include<cmath>
#include <stdlib.h>
#include <time.h> 

using namespace std;

const int num_C=12;
const int N=100;
const double pc=0.9;
const double pm=0.1;
const double ps=0.6;
const int genmax=2000;

double function(double x1,double x2)
{
    //return 20+x1*x1+x2*x2-10*(cos(2*3.14*x1))+cos(2*3.14*x2);
    //return pow(x1-1,2)+pow(x2,2);
    //return x1+x2;
    return abs(20)-abs(x1)-abs(x2);
}

int random(int low,int high)
{
    int k;
    double d;
    k=rand();
    k=(k!=RAND_MAX)? k:k-1;
    d=(double)k/((double)(RAND_MAX));
    k=(int)(d*(high-low+1));
    return (low+k);
}

class unit
{
public:
    vector<int> path;
    double cost;
    
    unit()
    {
        path.resize(num_C);
        for(int i=0;i<num_C;++i)
        {
            path[i]=random(0,9);
        }
        cal_cost();
    }

    void Copy(const unit& that)
    {
        path=that.path;
        cost=that.cost;
    }

    void Cross(unit& that)
    {
        int cross_point=random(0,num_C-1);
        for(int i=cross_point;i<num_C;++i)
        {
            int tmp=path[i];
            path[i]=that.path[i];
            that.path[i]=tmp;
        }
        cal_cost();
        that.cal_cost();
    }

    void Varation()
    {
        int i=random(0,num_C-1);
        int j=random(0,num_C-1);
        int tmp=path[i];
        path[i]=path[j];
        path[j]=tmp;
        cal_cost();
    }
    
    bool operator<(const unit& that)
    {
        return cost<that.cost;
    }

    void display()
    {
        pair<double,double> x=change();
        cout<<x.first<<" "<<x.second<<"     "<<cost<<endl;
    }

    pair<double,double> change()
    {
        double x1=0,x2=0;
        double coef=1.0;
        for(int i=1;i<=5;++i)
        {
            x1+=path[i]*coef;
            coef/=10.0;
        }
        
        coef=1.0;
        for(int i=7;i<=11;++i)
        {
            x2+=path[i]*coef;
            coef/=10.0;
        }

        x1= (path[0]>5) ? x1: -x1;
        x2= (path[6]>5) ? x2: -x2;
        return {x1,x2};
    }

    void cal_cost()
    {
        pair<double,double> x=change();
        cost=function(x.first,x.second);
    }
};

class Group
{
private:
    vector<unit> group;
public:
    Group();
    void Evolution();
    void display();
};

Group::Group()
{
    group.resize(N);
}

void Group::Evolution()
{
    int temp1,temp2,temp3,temp4,temp5;
    temp1=N*pc/2;
    temp2=N*(1-pc);
    temp3=N*(1-pc/2);
    temp4=N*(1-ps);
    temp5=N*ps;
    sort(group.begin(),group.end());
    for(int i=0;i<genmax;++i)
    {
        //选择
        for(int j=0;j<temp4;++j)
        {
            group[j+temp5].Copy(group[j]);
        }
        //交叉
        for(int j=0;j<temp1-1;j+=2)
        {
            group[temp2+j].Cross(group[temp3+j]);
        }
        //变异
        int flag=random(1,100);
        if((!flag>(i>100)) ?(5*100*pm):(100*pm))
        {
            group[random(0,N-1)].Varation();
        }
        sort(group.begin(),group.end());
        //cout<<"第"<<i<<"代结果：";
        group[0].display();
    }
}

void Group::display()
{
    for(auto& entry:group)
    {
        entry.display();
    }
}

int main()
{
    srand((unsigned)time(nullptr));
    Group* curgroup=new Group();
    curgroup->Evolution();
    system("pause");
    return 0;
}


