#include<map>
#include<set>
#include<iostream>
#include<queue>
#include<chrono>
#include<thread>
#include<future>
#include<functional>
#include<type_traits>


using namespace std;

struct cmp
{
    bool operator()(const int &a,const int &b) const 
    {
        return a>b;
    }
};

template<typename T,typename F=void>
struct has_insert:std::false_type{};

template<typename T>
struct has_insert<T,std::void_t<decltype(std::declval<T>().insert(std::declval<typename T::value_type>()))>>:std::true_type{};

template<typename T>
constexpr bool has_insert_v=has_insert<T>::value;

template<typename T,typename F=void>
struct has_push:std::false_type{};

template<typename T>
struct has_push<T,std::void_t<decltype(std::declval<T>().push(std::declval<typename T::value_type>()))>>:std::true_type{};

template<typename T>
constexpr bool has_push_v=has_push<T>::value;

template<typename Container>
int64_t test(Container c,unsigned int n)
{

    using T=typename std::decay_t<Container>::value_type;
    using ContainerType=typename std::decay_t<Container>;
    static_assert(is_same<T,int>::value,"Container must be int");
    //static_assert(has_insert_v<Container>,"Container must have insert method")

    auto btime=chrono::steady_clock::now();
    for(T i=0;i<n;i++)
    {
        if constexpr(has_insert_v<ContainerType>)
        {
            c.insert(i);
            //std::cout<<c.size()<<std::endl;
        }
        else if constexpr(has_push_v<ContainerType>)
        {
            c.push(i);
            //std::cout<<c.size()<<std::endl;
        }
    }
    auto etime=chrono::steady_clock::now();
    //std::cout<<c.size()<<std::endl;
    return chrono::duration_cast<chrono::milliseconds>(etime-btime).count();
}

template<typename CurCont,typename... Args>
std::vector<packaged_task<int64_t()>> global_test_impl(unsigned int n,CurCont&& cur,Args&&... args)
{
    std::vector<packaged_task<int64_t()>> tasks;
    packaged_task<int64_t()> task(bind(test<CurCont>,cur,n));
    tasks.emplace_back(std::move(task));
    if constexpr (sizeof...(args)>0)
    {
        auto&& tmp=global_test_impl(n,args...);
        tasks.insert(tasks.end(),make_move_iterator(tmp.begin()),make_move_iterator(tmp.end()));
    }
    return tasks;
}


template<typename... Args>
void global_test(unsigned int n,Args&&... args)
{
    std::vector<packaged_task<int64_t()>> tasks=global_test_impl(n,args...);
    std::vector<thread> threads;
    std::vector<future<int64_t>> results;
    for(auto&& i:tasks)
    {
        results.emplace_back(i.get_future());
        threads.emplace_back(move(i));
    }

    for_each(threads.begin(),threads.end(),mem_fn(&thread::join));
    for_each(results.begin(),results.end(),[](auto&& i){cout<<i.get()<<endl;});
}



int main()
{
    //map<int,int,cmp> mp;
    
    set<int,cmp> st;

    priority_queue<int,vector<int>,cmp> pq;
    std::cout<<has_insert_v<set<int,cmp>><<std::endl;
    std::cout<<has_insert_v<priority_queue<int,vector<int>,cmp>><<std::endl;
    std::cout<<has_push_v<set<int,cmp>><<std::endl;
    std::cout<<has_push_v<priority_queue<int,vector<int>,cmp>><<std::endl;
    global_test(100000,st,pq);
    std::cout<<st.size()<<std::endl;
    std::cout<<pq.size()<<std::endl;
    

    
    
    system("pause");
    return 0;
}