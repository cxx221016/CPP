#include"Polyfit.h"

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
}