#include<iostream>
#include<string>
#include<set>
#include<time.h>
#include"BIT.h"
using namespace std;

template<typename T>
struct Less
{
    bool operator()(const T& left, const T& right)
    {
        return left < right;
    }
};

template<typename K, typename V, typename Comp = Less<K>>
class SkipList
{
private:
    struct skip_list_node
    {
        int level;
        const K key;
        V value;
        skip_list_node** forward;
        
        skip_list_node():key{ 0 }, value{ 0 }, level{ 0 }, forward{0} {}
        skip_list_node(K key, V value, int level,skip_list_node* nxt=nullptr)
            :key(key), value(value), level(level)
        {
            forward = new skip_list_node*[level+1];
            for(int i=0;i<=level;++i) forward[i]=nxt;
        }
        ~skip_list_node()
        {
            delete[] forward;
        }
    };

    using node=skip_list_node;
    int level;
    int length;
    static const int MAXL = 32;
    static const int P=4;
    static const int S=0xFFFF;
    static const int PS=S/P;
    static const int INVALID=INT_MAX;
    node* head,*tail;
    Comp less;

    void init()
    {
        srand((unsigned)time(NULL));
        level=length=0;
        head->forward=new node*[MAXL+1];
        for(int i=0;i<=MAXL;++i) head->forward[i]=tail;
    }
    int random_level()
    {
        int lvl=1;
        while((rand()&S)<PS)
            lvl++;
        return lvl<MAXL?lvl:MAXL;
    }

    node* find(const K& key, node** update)
    {
        node* x=head;
        for(int i=level;i>=0;i--)
        {
            while(x->forward[i]!=tail && less(x->forward[i]->key, key))
                x=x->forward[i];
            update[i]=x;
        }
        x=x->forward[0];
        return x;
    }
public:
    struct Iter
    {
        node* p;
        Iter(node* p=nullptr):p(p){}
        Iter& operator++()
        {
            p=p->forward[0];
            return *this;
        }
        Iter operator++(int)
        {
            Iter tmp=*this;
            p=p->forward[0];
            return tmp;
        }

        bool operator==(const Iter& right)
        {
            return p==right.p;
        }
        bool operator!=(const Iter& right)
        {
            return p!=right.p;
        }
        node* operator->() const 
        {
            return p;
        }

        node& operator*() const
        {
            return *p;
        }

    };

    SkipList ():head(new node()),tail(new node()),less{Comp()}
    {
        init();
    }

    SkipList (const Comp& comp):head(new node()),tail(new node()),less{comp}
    {
        init();
    }

    void insert(const K& key, const V& value)
    {
        node* update[MAXL+1];
        node* x=find(key, update);
        if(x!=tail && x->key==key)
        {
            x->value=value;
            return;
        }
        int lvl=random_level();
        if(lvl>level)
        {
            lvl=++level;
            update[lvl]=head;
        }
        node* newnode=new node(key, value, lvl);
        for(int i=lvl;i>=0;i--)
        {
            x=update[i];
            newnode->forward[i]=x->forward[i];
            x->forward[i]=newnode;
        }
        length++;
    }

    bool erase(const K& key)
    {
        node* update[MAXL+1];
        node* x=find(key, update);
        if(x==tail || x->key!=key)
            return false;
        for(int i=0;i<=x->level;i++)
        {
            if(update[i]->forward[i]!=x)
                break;
            update[i]->forward[i]=x->forward[i];
        }
        delete x;
        while(level>0 && head->forward[level]==tail)
            level--;
        length--;
        return true;
    }

    Iter find(const K& key)
    {
        node* update[MAXL+1];
        node* x=find(key, update);
        if(x==tail) return tail;
        if(x->key!=key) return tail;
        return Iter(x);
    }

    bool count(const K& key)
    {
        node* update[MAXL+1];
        node* x=find(key, update);
        if(x==tail) return false;
        if(x->key!=key) return false;
        return true;
    }

    Iter begin()
    {
        return Iter(head->forward[0]);
    }

    Iter end()
    {
        return Iter(tail);
    }
};

int main()
{

    {
        //使用lambda
        auto cmp = [](const string& a, const string& b) {return a.length() < b.length(); };
        SkipList< string, int, decltype(cmp)> list(cmp);
        list.insert("aab", 1321);
        list.insert("hello", 54342);
        list.insert("world", 544);
        for (auto it = list.begin(); it != list.end(); it++) {
            cout << it->key << " " << it->value << endl;
        }
    }

    cout << "==================================" << endl;
    
    {
        //使用仿函数
        struct cmp {
            bool operator()(int a, int b) {
                return a > b;
            }
        };
        SkipList < int, int, cmp> list{};
        for (int i = 1; i <= 10; i++)list.insert(rand()%20, rand());
        for (auto it = list.find(10); it != list.end(); it++) {
            cout << it->key << " " << it->value << endl;
        }
    }

    cout << "==================================" << endl;

    {
        //默认小于号
        SkipList<int, int>list;
        list.insert(1, 3);
        list.insert(1, 3);
        list.insert(4, 3);
        list.insert(5, 3);
        list.insert(1, 3);
        list.insert(4, 3);
        for (auto it = list.begin(); it != list.end();it++) {
            cout << it->key << " " << it->value << endl;
        }
    }

    system("pause");
    
}