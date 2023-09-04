#include<iostream>
#include<vector>
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include<fstream>

using namespace std;

#define RANDOM rand()/32767.0

const int Layer_Max=5;
const double PI=3.1415927;
const int Layer_number[Layer_Max]={2,4,4,2,1};
const int Neural_Max=4;
const int InMax=21;


//D:/MY_CODE/CPP/Artificial Neural Network/OUT/

ofstream Out_W_File("D:/MY_CODE/CPP/Artificial Neural Network/OUT/All_W.txt",ios::out);
ofstream Out_Error("D:/MY_CODE/CPP/Artificial Neural Network/OUT/Error.txt",ios::out);

class BP
{
private:
    vector<vector<vector<double>>> W=vector<vector<vector<double>>> (Layer_Max,vector<vector<double>>(Neural_Max,vector<double>(Neural_Max)));
    vector<vector<double>> Input_Net=vector<vector<double>>(2,vector<double>(InMax));
    vector<vector<double>> Out_Exp=vector<vector<double>>(InMax,vector<double>(InMax));
    vector<vector<double>> Layer_Node=vector<vector<double>>(Layer_Max,vector<double>(Neural_Max));
    vector<vector<double>> D=vector<vector<double>>(Layer_Max,vector<double>(Neural_Max));
    double Study_Speed;

    double e;

public:
    BP();
    void BP_print();
    double F(double x);
    double Y(double x1,double x2);
    double NetWorkOut(int x1,int x2);
    void AllLayer_D(int x1,int x2);
    void Change_W();
    void Train();
    void After_Train_Out();
    double Cost(double out,double Exp);
};

BP::BP()
{
    srand(time(nullptr));
    for(int i=1;i<Layer_Max;++i)
    {
        for(int j=0;j<Layer_number[i];++j)
        {
            for(int k=0;k<Layer_number[i-1]+1;++k)
            {
                W[i][j][k]=RANDOM;
            }
        }
    }
    for(int i=0;i<InMax;i++)
    {
        Input_Net[0][i]=i*0.05;
        Input_Net[1][i]=1-i*0.05;
    }

    for(int i=0;i<InMax;++i)
    {
        for(int j=0;j<InMax;++j)
        {
            Out_Exp[i][j]=Y(Input_Net[0][i],Input_Net[1][j]);
            Out_Exp[i][j]/=3.0000000;
        }
    }
    Study_Speed=0.5;

    e=0.01;
}

double BP::F(double x)
{
    return (1.0/(1+exp(-x)));
}

double BP::Y(double x1,double x2)
{
    double temp=pow(x1-1,4)+2*pow(x2,2);
    return temp;
}

double BP::Cost(double Out,double Exp)
{
    return pow(Out-Exp,2);
}

double BP::NetWorkOut(int x1,int x2)
{
    int i,j,k;
    vector<vector<double>> N_node(Layer_Max,vector<double>(Neural_Max));
    N_node[0][0]=Input_Net[0][x1];
    Layer_Node[0][0]=Input_Net[0][x1];
    N_node[0][1]=Input_Net[1][x2];
    Layer_Node[0][1]=Input_Net[1][x2];

    for(i=1;i<Layer_Max;++i)
    {
        for(j=0;j<Layer_number[i];++j)
        {
            N_node[i][j]=0.0;
            for( k=0;k<Layer_number[i-1];++k)
            {
                N_node[i][j]+=Layer_Node[i-1][k]*W[i][j][k];
            }
            N_node[i][j]-=W[i][j][k];
            Layer_Node[i][j]=F(N_node[i][j]);
        }
    }
    return Layer_Node[Layer_Max-1][0];
}

void BP::AllLayer_D(int x1,int x2)
{
    double temp;
    D[Layer_Max-1][0]=Layer_Node[Layer_Max-1][0]*(1-Layer_Node[Layer_Max-1][0])*(Layer_Node[Layer_Max-1][0]-Out_Exp[x1][x2]);
    for(int i=Layer_Max-1;i>0;--i)
    {
        for(int j=0;j<Layer_number[i-1];++j)
        {
            temp=0;
            for(int k=0;k<Layer_number[i];++k)
            {
                temp+=W[i][k][j]*D[i][k];
            }
            D[i-1][j]=Layer_Node[i-1][j]*(1-Layer_Node[i-1][j])*temp;
        }
    }
}

void BP::Change_W()
{
    int k=0;
    for(int i=1;i<Layer_Max;++i)
    {
        for(int j=0;j<Layer_number[i];++j)
        {
            for( k=0;k<Layer_number[i-1];++k)
            {
                W[i][j][k]-=Study_Speed*D[i][j]*Layer_Node[i-1][k];
            }
            W[i][j][k]+=Study_Speed*D[i][j];
        }
    }
}

void BP::Train()
{
    int i,j;
    int ok=0;
    double Out;
    long int count=0;
    double err;
    ofstream Out_count("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/Out_count.txt",ios::out);
    ofstream outWFile1("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/W[2][0][0].txt",ios::out);
    ofstream outWFile2("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/W[2][1][1].txt",ios::out);
    ofstream outWFile3("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/W[1][0][0].txt",ios::out);
    ofstream outWFile4("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/W[1][1][0].txt",ios::out);
    ofstream outWFile5("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/W[3][0][1].txt",ios::out);

    while(ok<441)
    {
        count++;
        for(i=0,ok=0;i<InMax;++i)
        {
            for(j=0;j<InMax;++j)
            {
                Out=NetWorkOut(i,j);
                AllLayer_D(i,j);
                err=Cost(Out,Out_Exp[i][j]);
                if(err<e) ok++;
                else Change_W();
            }
        }
        if((count%1000)==0)
        {
            cout<<count<<" "<<err<<" "<<ok<<endl;
            Out_count<<count<<",";
            Out_Error<<err<<",";
            outWFile1<<W[2][0][0]<<",";
            outWFile2<<W[2][1][1]<<",";
            outWFile3<<W[1][0][0]<<",";
            outWFile4<<W[1][1][0]<<",";
            outWFile5<<W[3][0][1]<<",";
            for(int p=1;p<Layer_Max;++p)
            {
                for(int j=0;j<Layer_number[p];++j)
                {
                    for(int k=0;k<Layer_number[p-1]+1;++k)
                    {
                        Out_W_File<<'W'<<'['<<p<<']'<<'['<<j<<']'<<'['<<k<<']'<<'='<<W[p][j][k]<<"<<";
                    }
                }
            }
            Out_W_File<<'\n'<<'\n';
        }
    }
    cout<<err<<endl;
}

void BP::BP_print()
{
    cout<<"训练后的权系数"<<endl;
    for(int i=1;i<Layer_Max;++i)
    {
        for(int j=0;j<Layer_number[i];++j)
        {
            for(int k=0;k<Layer_number[i-1]+1;++k)
            {
                cout<<W[i][j][k]<<" ";
            }
            cout<<endl;
        }
    }
    cout<<endl<<endl;
}

void BP::After_Train_Out()
{
    ofstream Out_x1("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/Out_x1.txt",ios::out);
    ofstream Out_x2("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/Out_x2.txt",ios::out);
    ofstream Out_Net("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/Out_Net.txt",ios::out);
    ofstream Out_Exp("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/Out_Exp.txt",ios::out);
    ofstream W_End("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/W_End.txt",ios::out);
    ofstream Q_End("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/Q_End.txt",ios::out);
    ofstream Array("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/Array.txt",ios::out);
    ofstream Out_x11("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/x1.txt",ios::out);
    ofstream Out_x22("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/x2.txt",ios::out);
    ofstream Result1("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/result1.txt",ios::out);
    ofstream Out_x111("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/x11.txt",ios::out);
    ofstream Out_x222("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/x22.txt",ios::out);
    ofstream Result2("D:/MY_CODE/VS_CODE/Artificial Neural Network/OUT/result2.txt",ios::out);

    for(int i=0;i<InMax;++i)
    {
        for(int j=0;j<InMax;++j)
        {
            Out_x11<<Input_Net[0][i]<<",";
            Out_x22<<Input_Net[1][j]<<",";
            Result1<<3*NetWorkOut(i,j)<<",";
            Out_x1<<Input_Net[0][i]<<",";
            Array<<Input_Net[0][i]<<" ";
            Out_x2<<Input_Net[1][j]<<",";
            Array<<Input_Net[1][j]<<" ";
            Out_Net<<3*NetWorkOut(i,j)<<",";
            Array<<Y(Input_Net[0][i],Input_Net[1][j])<<" ";
            Out_Exp<<Y(Input_Net[0][i],Input_Net[1][j])<<",";
            Array<<3*NetWorkOut(i,j)<<" ";
            Array<<'\n';
        }
        Out_x1<<'\n';
        Out_x2<<'\n';
        Out_x11<<'\n';
        Out_x22<<'\n';
        Result1<<'\n';
    }

    for(int j=0;j<InMax;++j)
    {
        for(int i=0;i<InMax;++i)
        {
            Out_x111<<Input_Net[0][i]<<",";
            Out_x222<<Input_Net[1][j]<<",";
            Result2<<3*NetWorkOut(i,j)<<",";
        }
        Out_x111<<'\n';
        Out_x222<<'\n';
        Result2<<'\n';
    }

    for(int i=1;i<Layer_Max;++i)
    {
        for(int j=0;j<Layer_number[i];++j)
        {
            for(int k=0;k<Layer_number[i-1]+1;++k)
            {
                W_End<<W[i][j][k]<<",";
            }
        }
    }
}

int main()
{
    BP B;
    B.Train();
    B.BP_print();
    B.After_Train_Out();
    system("pause");
    return 0;
}