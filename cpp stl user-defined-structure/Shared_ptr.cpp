#include <memory>
#include <iostream>
template <typename T>
class Shared_ptr
{
private:
    T *ptr;
    unsigned int *count;

public:
    Shared_ptr() : ptr(nullptr), count(nullptr) {}
    Shared_ptr(T *p) : ptr(p), count(new unsigned int(1)) {}
    Shared_ptr(const Shared_ptr &p) : ptr(p.ptr), count(p.count)
    {
        if (ptr)
            (*count)++;
    }
    ~Shared_ptr()
    {
        if (ptr)
        {
            (*count)--;
            if (*count == 0)
            {
                delete ptr;
                delete count;
            }
        }
    }
    Shared_ptr &operator=(const Shared_ptr &p)
    {
        if (this->ptr == p.ptr)
        {
            return *this;
        }
        if (ptr)
        {
            (*count)--;
            if (count == 0)
            {
                delete ptr;
                delete count;
            }
        }
        this->ptr = p.ptr;
        this->count = p.count;
        if (this->count)
            (*count)++;
        return *this;
    }
    Shared_ptr(Shared_ptr &&p)
    {
        std::swap(this->ptr, p.ptr);
        std::swap(this->count, p.count);
    }
    Shared_ptr &operator=(Shared_ptr &&p)
    {
        Shared_ptr tmp(std::move(p));
        std::swap(this->ptr, tmp.ptr);
        std::swap(this->count, tmp.count);
        return *this;
    }

    unsigned int use_count()
    {
        if (!ptr)
            return 0;
        return *count;
    }
};

template <typename T>
class SharedPtr
{
private:
    T *ptr;
    unsigned int *count;

public:
    SharedPtr() : ptr(nullptr), count(nullptr) {}
    SharedPtr(T *_ptr) : ptr(_ptr), count(new unsigned int(1))
    {
        }
    ~SharedPtr()
    {
        if (ptr)
        {
            if (--(*count) == 0)
            {
                delete ptr;
                delete count;
            }
        }
    }
    SharedPtr(const SharedPtr &other) : ptr(other.ptr), count(other.count)
    {
        if (ptr)
        {
            ++(*count);
        }
    }
    SharedPtr &operator=(const SharedPtr &other)
    {
        if (this->ptr == other.ptr)
        {
            return *this;
        }
        if (this->ptr)
        {
            if (--(*count) == 0)
            {
                delete ptr;
                delete count;
            }
        }
        this->ptr = other.ptr;
        this->count = other.count;
        if (this->ptr)
            ++*count;
        return *this;
    }

    SharedPtr(SharedPtr &&other)
    {
        swap(*this, other);
    }

    SharedPtr &operator=(SharedPtr &&other)
    {
        SharedPtr tmp(std::move(other));
        swap(tmp, *this);
        return *this;
    }

    unsigned int use_count()
    {
        if (!ptr)
            return 0;
        return *count;
    }
    template <typename U>
    friend void swap(SharedPtr<U> &p1, SharedPtr<U> &p2);
};

template <typename T>
void swap(SharedPtr<T> &p1, SharedPtr<T> &p2)
{
    std::swap(p1.ptr, p2.ptr);
    std::swap(p1.count, p2.count);
}

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */

void test_use_count()
{
    SharedPtr<int> p(new int(1));
    SharedPtr<int> q(new int(2));
    SharedPtr<int> r(p);
    SharedPtr<int> s(p);
    std::cout << p.use_count() << std::endl;
    std::cout << q.use_count() << std::endl;
    q = std::move(p);
}

int main()
{

    Shared_ptr<int> p(new int(1));
    Shared_ptr<int> q(new int(2));
    Shared_ptr<int> r(p);
    Shared_ptr<int> s(p);
    std::cout << p.use_count() << std::endl;
    std::cout << q.use_count() << std::endl;
    q = std::move(p);
    std::cout << r.use_count() << std::endl;
    std::cout << s.use_count() << std::endl;
    std::cout << q.use_count() << std::endl;

    Shared_ptr<int> t;
    auto u = std::move(t);
    auto null1(u);
    auto null2(u);
    auto null3(u);
    std::cout << u.use_count() << std::endl;
    std::cout << null1.use_count() << std::endl;
    std::cout << null2.use_count() << std::endl;
    std::cout << null3.use_count() << std::endl;

    // p=std::move(q);
    // std::cout<<p.use_count()<<std::endl;
    std::cout << "-------------------------" << std::endl;
    test_use_count();

    system("pause");
    return 0;
}