#include<vector>
using namespace std;

class Matrix
{
public:
    template<typename T>
    vector<vector<T>> mul(const vector<vector<T>>& a,const vector<vector<T>>& b)
    {
        int m=a.size(),n=a[0].size(),p=b[0].size();
        vector<vector<T>> res(m,vector<T>(p,0));
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<p;++j)
            {
                for(int k=0;k<n;++k)
                {
                    res[i][j]=(res[i][j]+a[i][k]*b[k][j])%1000000007;
                }
            }
        }
        return res;
    }

    template<typename T>
    vector<vector<T>> pow(vector<vector<T>>& a,int n)
    {
        int m=a.size();
        vector<vector<T>> res(m,vector<T>(m,0));
        for(int i=0;i<m;++i)
        {
            res[i][i]=1;
        }
        while(n)
        {
            if(n&1) res=mul(res,a);
            a=mul(a,a);
            n>>=1;
        }
        return res;
    }
};