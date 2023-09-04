#include<iostream>
#include<stdio.h>
#include<vector>
#include<assert.h>

using namespace std;

double hypothose(vector<double>& w ,int feature_num ,vector<double>& training_set)
{
    double sum=0;
    for(int i=0;i<feature_num;++i)
    {
        sum+=w[i]*training_set[i];
    }
    if(sum>0) return 1;
    else return 0;
}

void perception(int feature_num,int training_num,double a,int times,vector<vector<double>>& training_set,vector<double>& w)
{
    while(times--)
    {
        vector<double> delta_w(feature_num,0);
        for(int i=0;i<training_num;++i)
        {
            for(int j=0;j<feature_num;++j)
            {
                delta_w[j]+=a*(training_set[i][feature_num]-hypothose(w,feature_num,training_set[i]))*training_set[i][j];
            }
        }
        for(int i=0;i<feature_num;++i)
        {
            w[i]+=delta_w[i];
        }
    }
}
int main()
{
    int feature_num,training_num,times;
    double a;
    freopen("D:/MY_CODE/CPP/Artificial Neural Network/PERCPTION/percption data.txt","r",stdin);
    freopen("D:/MY_CODE/CPP/Artificial Neural Network/PERCPTION/percption out.txt","w",stdout);
    cin>>feature_num>>training_num>>a>>times;
    {
        vector<vector<double>> training_set(training_num,vector<double>(feature_num+2,1));
        for(auto& train:training_set)
        {
            for(int i=1;i<=feature_num+1;++i)
            {
                cin>>train[i];
            }
        }
 
        vector<double> w(feature_num+1);
        for(auto& wei:w)
        {
            cin>>wei;
        }
        perception(feature_num+1,training_num,a,times,training_set,w);
        for(auto& wei:w)
        {
            cout<<wei<<" ";
        }
        cout<<endl;
        fclose(stdin);
        fclose(stdout);
        cin.clear();
        cout.clear();
        freopen("CON","w",stdout);
        system("pause");
        return 0;
    }

}