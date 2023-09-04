#ifndef POLYFIT_H
#define POLYFIT_H
#include<vector>
#include<cmath>
#include<algorithm>
#include<numeric>

class Polyfit
{
protected:
    double getY(const double& x) const
    {
        double res=0.0;
        for(size_t i=0;i<(Degree+1);++i)
        {
            res+=coefficients[i]*pow((double)x,(int)i);
        }
        return res;
    }

    static double Mean(const std::vector<double>& vec)
    {
        double sum=0;
        sum=std::accumulate(vec.begin(),vec.end(),0.0);
        return sum/vec.size();
    }


    void CalError(const std::vector<double>& x,const std::vector<double>& y,double& ssr,double& sse,double& rmse)
    {
        double mean_y=Mean(y);
        double yi=0;
        for(size_t i=0;i<x.size();++i)
        {
            yi=getY(x[i]);
            ssr+=pow(yi-mean_y,2);
            sse+=pow(yi-y[i],2);
        }
        rmse=sqrt(sse/x.size());
    }
    static void PolynomialFit(const std::vector<double>& Mtx,const std::vector<double>& Mty,std::vector<double>& coefficients);
    static void GuassElimination(std::vector<std::vector<double>>& matrix,std::vector<double>& coefficients);
public:
    Polyfit(std::vector<double>& _Mtx,std::vector<double>& _Mty,int _Degree):Mtx(_Mtx),Mty(_Mty),Degree(_Degree),ssr(0.0),sse(0.0),rmse(0.0),hasfinished(false)
    {
        coefficients.resize(_Degree+1,0);
        PolynomialFit(Mtx,Mty,coefficients);
        hasfinished=true;
        CalError(Mtx,Mty,ssr,sse,rmse);
    }
    std::vector<double> getcoef()
    {
        return coefficients;
    }

    double Cal(double x)
    {
        double y=0.0;
        for(int i=0;i<=Degree;++i)
        {
            y+=pow(x,double(i))*coefficients[i];
        }
        return y;
    }
    ~Polyfit(){};
private:
    int Degree;
    std::vector<double> coefficients;
    const std::vector<double>& Mtx;
    const std::vector<double>& Mty;
    bool hasfinished;
    double ssr;
    double sse;
    double rmse;
};
/*

void Polyfit::PolynomialFit(const std::vector<double>& Mtx,const std::vector<double>& Mty, std::vector<double>& coefficients)
{
    int n=Mtx.size();
    int Degree=coefficients.size()-1;
    std::vector<double> X(2*Degree+1,0);
    std::vector<double> Y(Degree+1,0);
    std::vector<std::vector<double>> Mat(Degree+1,std::vector<double>(Degree+2,0));
    for(int i=0;i<2*Degree+1;++i)
    {
        for(int j=0;j<n;++j)
        {
            X[i]+=pow(Mtx[j],i);
        }
    }

    for(int i=0;i<Degree+1;++i)
    {
        for(int j=0;j<n;++j)
        {
            Y[i]+=pow(Mtx[j],i)*Mty[j];
        }
    }

    for(int i=0;i<Degree+1;++i)
    {
        for(int j=0;j<Degree+1;++j)
        {
            Mat[i][j]=X[i+j];
        }
        Mat[i][Degree+1]=Y[i];
    }

    GuassElimination(Mat,coefficients);
}

void Polyfit::GuassElimination(std::vector<std::vector<double>>& matrix,std::vector<double>& coefficients)
{
    int Degree=coefficients.size()-1;
    for(int i=0;i<Degree;++i)
    {
        for(int k=i+1;k<Degree+1;++k)
        {
            double t=matrix[k][i]/matrix[i][i];
            for(int j=0;j<Degree+2;++j)
            {
                matrix[k][j]-=t*matrix[i][j];
            }
        }

        for(int i=Degree;i>=0;--i)
        {
            coefficients[i]=matrix[i][Degree+1];
            for(int j=0;j<Degree+1;++j)
            {
                if(j!=i) coefficients[i]-=matrix[i][j]*coefficients[j];
            }

            coefficients[i]/=matrix[i][i];
        }
    }
}*/
#endif