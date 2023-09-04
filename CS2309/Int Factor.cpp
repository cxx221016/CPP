//#include "std_lib_facilities.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;


//¶¨Òåmainº¯Êý
int main() 
{		
    bool exercise1=true;
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
    {
        //第二关执行代码
         

    }
    
    
	/********** End **********/
  	return 0;
}