#include<vector>
#include<random>
#include<ctime>
#include<iostream>
#include<iomanip>
class MaxHeap
{
private:
    std::vector<int> data;
    int n;
    void down(int hole)
    {
        int child;
        int tmp=data[hole];
        for(;hole*2<=n;hole=child)
        {
            child=hole*2;
            if(child<n&&data[child+1]>data[child])
            {
                child++;
            }
            if(data[child]>tmp)
            {
                data[hole]=data[child];
            }
            else 
            {
                break;
            }

        }
        data[hole]=tmp;
    }

    void doubleSpace()
    {
        data.resize(data.size()*2);
    }

public:
    MaxHeap(const std::vector<int>& other):n(other.size())
    {
        data.resize(n+1);
        for(int i=1;i<=n;++i)
        {
            data[i]=other[i-1];
        }
        for(int i=n/2;i>=1;--i)
        {
            down(i);
        }
    }

    int pop()
    {
        int val=data[1];
        data[1]=data[n--];
        down(1);

        return val;
    }

    int push(int x)
    {
        if(n==data.size()-1)
        {
            doubleSpace();
        }
        int hole=++n;
        for(;hole>1&&x>data[hole/2];hole/=2)
        {
            data[hole]=data[hole/2];
        }
        data[hole]=x;
    }

    bool empty()
    {
        return n==0;
    }

};

int main()
{
    std::default_random_engine e(time(nullptr));
    std::uniform_int_distribution<int> u(0,100);
    int testnum=10;
    int arraynum=10;
    int insertnum=10;
    while(testnum--)
    {
        std::vector<int> array;
        std::cout<<"array: ";
        for(int i=0;i<arraynum;++i)
        {
            array.push_back(u(e));
            std::cout<<std::setw(3)<<array.back()<<" ";
        }
        std::cout<<std::endl;
        MaxHeap heap(array);
        std::cout<<"heap: ";

        while(!heap.empty())
        {
            std::cout<<std::setw(3)<<heap.pop()<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"--------------------------------------------------";
        std::cout<<std::endl;




    }
    system("pause");

}