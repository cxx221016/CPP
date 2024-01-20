#include<memory>
#include<iostream>
template<typename T>
class Shared_ptr
{
private:
    T* ptr;
    unsigned int  * count;
public:
    Shared_ptr():ptr(nullptr),count(nullptr){}
    Shared_ptr(T* p):ptr(p),count(new unsigned int(1)){}
    Shared_ptr(const Shared_ptr& p):ptr(p.ptr),count(p.count){(*count)++;}
    Shared_ptr & operator=(const Shared_ptr& p)
    {
        if(this->ptr==p.ptr)
        {
            return *this;
        }
        if(ptr)
        {
            (*count)--;
            if(count==0)
            {
                delete ptr;
                delete count;
            }
        }
        this->ptr=p.ptr;
        this->count=p.count;
        if(this->count) (*count)++;
        return *this;
    }
    Shared_ptr(Shared_ptr&& p)
    {
        std::swap(this->ptr,p.ptr);
        std::swap(this->count,p.count);
    }
    Shared_ptr& operator=(Shared_ptr&& p)
    {
        Shared_ptr tmp(std::move(p));
        std::swap(this->ptr,tmp.ptr);
        std::swap(this->count,tmp.count);
        return *this;
    }

    unsigned int use_count()
    {
        return *count;
    }
};

int main()
{
    Shared_ptr<int> p(new int(1));
    Shared_ptr<int> q(new int (2));
    Shared_ptr<int> r(p);
    Shared_ptr<int> s(p);
    std::cout<<p.use_count()<<std::endl;
    std::cout<<q.use_count()<<std::endl;
    q=std::move(p);
    std::cout<<r.use_count()<<std::endl;
    std::cout<<s.use_count()<<std::endl;
    std::cout<<q.use_count()<<std::endl;
    
    // p=std::move(q);
    // std::cout<<p.use_count()<<std::endl;
    
    system("pause");
    return 0;
}