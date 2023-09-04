//#include "std_lib_facilities.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<iomanip>
#include<regex>
using namespace std;

int input=1, output=0;

int count(double x)
{
    int res=0;
    if(x<0) {res++;x=-x;}
    int y=(int)x;
    while(y)
    {
        y/=10;
        ++res;
    }
    return res;
}

double keep(double x)
{
    int flag=x>=0;
    if(flag) return floor(x * 10000.000f) / 10000.000f;
    else return -(floor(abs(x) * 10000.000f+0.1 ) / 10000.000f);
}

pair<int,double> get(const string& str)
{
    int i=0,n=str.size();
    int begin=0;
    double flag=1.0000;
    if(str[i]=='-') {flag=-1.0000;++i;begin=1;}
    else if(str[i]=='+') {++i;begin=1;}

    while(i<n&&str[i]!='x')
    {
        ++i;
    }

    double tmp=1.0000;
    if(i!=begin) tmp=stof(str.substr(begin,i-begin).c_str());
    double sec=tmp;

    int fir=0;
    if(i==n) return make_pair(fir,sec*flag);
    else if(i==n-1) return make_pair(1,sec*flag);
    else
    {
        fir=str[i+2]-'0';
        return make_pair(fir,sec*flag);
    }
}

struct Type
{
    double coef;  // 系数
    int exp;  // 幂指数
};

template <class elemType>
struct Node
{
    elemType data;
    Node* next;
};

template <class elemType>
class Polynomial
{
    private:
        Node<elemType>* head;
    public:
        Polynomial(const Polynomial &L);
        Polynomial();
        Polynomial(const string& str);
        void divPoly(const Polynomial &L1, const Polynomial &L2,Polynomial &LY);//L1/L2
        void insert(Node<elemType>* t);
        void makeFull();
        void dispPoly();//显示一个多项式
        void dis();
        void clear();//释放多项式空间
        ~Polynomial(){clear(); delete head;};
};

template <class elemType>
Polynomial<elemType>::Polynomial(const Polynomial &L)
{
    head=new Node<elemType>();
    Node<elemType> *p,*tmp,*q;
    p=head;q=L.head->next;
    while(q)
    {
        tmp= new Node<elemType>();
        tmp->data.coef=q->data.coef;
        tmp->data.exp=q->data.exp;
        tmp->next=nullptr;
        p->next=tmp;
        p=tmp;
        q=q->next;
    }
}

template <class elemType>
Polynomial<elemType>::Polynomial()
{
    head=new Node<elemType>();
}

template <class elemType>
Polynomial<elemType>::Polynomial(const string& str)
{
    input+=str.size();
    head=new Node<elemType>();
    map<int,double> mp;
    int len=str.size();
    int i=0,j=0;
    if(str[0]=='-') ++i;
    while(i<len)
    {
        string tmp;
        while(i<len&&(str[i]!='+'&&str[i]!='-')) {++i;}
        tmp=str.substr(j,i-j);
        j=i++;
        mp[get(tmp).first]+=get(tmp).second;
    }
    Node<elemType> *p,*tmp;
    p=head;
    for(auto iter=mp.rbegin();iter!=mp.rend();++iter)
    {
        tmp= new Node<elemType>();
        tmp->data.coef=iter->second;
        tmp->data.exp=iter->first;
        tmp->next=nullptr;
        p->next=tmp;
        p=tmp;
    }
}

template <class elemType>
void Polynomial<elemType>::divPoly(const Polynomial &L1, const Polynomial &L2,Polynomial &LY)
{
    Node<elemType> *p1,*p2,*p3,*tmp;
    p1=L1.head->next;
    p2=L2.head->next;
    p3=head;
    while(p1&&p1->data.exp>=p2->data.exp)
    {
        double newcoef=p1->data.coef/p2->data.coef;
        int newexp=p1->data.exp-p2->data.exp;
        tmp=new Node<elemType>();
        tmp->data.coef=newcoef;
        tmp->data.exp=newexp;
        p3->next=tmp;
        tmp->next=nullptr;
        p3=tmp;
        Node<elemType>* q1=p1;
        Node<elemType>* q2=p2;
        while(q2)
        {
            q1->data.coef=1.0*(q1->data.coef-newcoef*q2->data.coef);
            q1=q1->next;
            q2=q2->next;
        }
        p1=p1->next;
    }
    LY.head->next=p1;
}
template <class elemType>
void Polynomial<elemType>::insert(Node<elemType>* t)
{
    Node<elemType>* add;
    add=new Node<elemType>();
    add->data.exp=t->data.exp-1;
    add->data.coef==0.0000;
    add->next=t->next;
    t->next=add;
}

template <class elemType>
void Polynomial<elemType>::makeFull()
{
    Node<elemType>* p=head->next;
    for(;p->next;p=p->next)
    {
        if(p->data.exp!=p->next->data.exp+1)
        {
            insert(p);
        }
    }
    Node<elemType>* q;
    q=new Node<elemType>();
    while(p->data.exp!=0)
    {
        q->data.coef=0.0000;
        q->data.exp=p->data.exp-1;
        p->next=q;
        q->next=nullptr;
        p=p->next;
    }
}

template <class elemType>
void Polynomial<elemType>::dis()
{
    Node<elemType> *p;
    p=head->next;
    while(p)
    {
        if(p->data.coef==0) {}
        else if(p->data.exp>1)
        {
            if(p==head->next) {}
            else if(p->data.coef>0) {output++;}

            output+=7+count(p->data.coef)+count(p->data.exp);
        }
        else if(p->data.exp==1)
        {
            if(p==head->next) {}
            else if(p->data.coef>0) output++;
            
            output+=6+count(p->data.coef);
        }
        else 
        {
            if(p==head->next) {}
            else if(p->data.coef>0) output++;

            output+=5+count(p->data.coef);
        }
        p=p->next;
    }

}

template <class elemType>
void Polynomial<elemType>::dispPoly()
{
    Node<elemType> *p;
    p=head->next;
    if(!p) {cout<<"0.0000";return;}
    while(p->next&&p->data.coef==0)
    {
        p=p->next;
    }
    if(p->data.coef==0) {cout<<"0.0000";return;}
    while(p)
    {
        if(p->data.coef==0) {}
        else if(p->data.exp>1)
        {
            if(p==head->next) {}
            else if(p->data.coef>0) {cout<<"+";}

            cout<<fixed<<setprecision(4)<<keep(p->data.coef)<<"x^"<<p->data.exp;
        }
        else if(p->data.exp==1)
        {
            if(p==head->next) {}
            else if(p->data.coef>0) cout<<"+";
            
            cout<<fixed<<setprecision(4)<<keep(p->data.coef)<<"x";
        }
        else 
        {
            if(p==head->next) {}
            else if(p->data.coef>0) cout<<"+";

            cout<<fixed<<setprecision(4)<<keep(p->data.coef);
        }
        p=p->next;
    }

}

template <class elemType>
void Polynomial<elemType>::clear()
{
    Node<elemType> *p,*q;
    p=head->next;
    head->next=nullptr;
    while(p)
    {
        q=p->next;
        delete p;
        p=q;
    }
}

//¶¨Òåmainº¯Êý
int main() 
{		
    /*bool exercise1=false;
    if(exercise1)    
    {
    //第一关执行代码
        string str;          
        getline(cin,str);    
        int cinlen=str.size();
        int coutlen=0;
        int n=stoi(str);
        if(n==1)
        {
            cout<<"1:7"<<endl<<"1 1"<<endl<<"1 1";
            system("pause");
            return 0;
        }
        //枚举法
        string res1;
        for(int i=2;i<n;++i)
        {
            if(n%i==0)
            {
                res1+=" "+to_string(i);coutlen++;
            }
        }
        coutlen+=2;
        res1=to_string(coutlen)+" "+"1"+res1+" "+to_string(n);
        //因式分解法
        vector<int> p;
        string res2;
        int tmp=n;
        for(int i=2;i<n;++i)
        {
            if(tmp==1) break;
            while(tmp!=1&&tmp%i==0)
            {
                p.push_back(i);
                tmp/=i;
            }
        }
        sort(p.begin(),p.end());
        set<int> seen;
        vector<int> result(1,1);seen.insert(1);
        for(int i=0;i<p.size();++i)
        {
            int cursize=result.size();
            for(int j=0;j<cursize;++j)
            {
                int tmp=result[j]*p[i];
                if(!seen.count(tmp))
                {
                    result.push_back(tmp);
                    seen.insert(tmp);
                }
            }
        }
        sort(result.begin(),result.end());
        res2+=to_string(coutlen);
        for(auto& num:result)
        {
            res2+=" "+to_string(num);
        }
        if(p.size()==0) res2+=" "+to_string(n);
        coutlen=res1.size()*2+1;
        cout<<cinlen<<":"<<coutlen<<endl;
        cout<<res1<<endl<<res2;
        system("pause");
    }   
    else     
    {*/
        //第二关执行代码
        string str1;
        string str2;
        cin>>str1;
        cin>>str2;
        regex polyPattern("^([-+]?([0-9]*\.?[0-9]+)?(x(\\^[+-]?[0-9]+)?)?)+$"); 
        if(!regex_match(str1,polyPattern)||!regex_match(str2,polyPattern)||str2[0]=='0')
        { 
            cout<<"error"<<endl<<"error"<<endl<<"error"<<endl<<"error";
            return 0;
        }
        Polynomial<Type> L1(str1);
        L1.dispPoly();
        Polynomial<Type> L2(str2);
        Polynomial<Type> L3;
        Polynomial<Type> L4;
        L3.divPoly(L1,L2,L4);
        output+=3;
        cout<<endl;
        L2.dispPoly();
        cout<<endl;
        L3.dispPoly();
        cout<<endl;
        L4.dispPoly();
    //}
    
    
	/********** End **********/
  	return 0;
}