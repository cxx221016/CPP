#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<string>
using namespace std;
#define MAX  100
vector<vector<double>> R(MAX,vector<double>(MAX));
/*
@to do:  获取自变量x对应的函数值
@param x 
*/
double getRombergFuntion(float x) {
	return log(x);
}
/*
@to do:自定义实现x的y的整数次幂的结果
@param x: x
@param y: y
@return 返回x的y次幂的结果int
*/

/*
@to do:获取荣贝格算法的n行打印数据
@param a:积分下限
@param b:积分上限
@param n:要打印的行数
*/
void getRombergValue(double a,double b,int n) 
{
	//获取初始值
	R[1][1] = (b-a)*(getRombergFuntion(a)+ getRombergFuntion(b))/2;
	//步长h
	double h = 0.0f;
	for (int  i = 2; i <= n; i++)
	{
		//计算当前步长
		h = (b - a) / pow(2,i-1);
		double sum = 0.0f;
		for (int j = 1; j <= pow(2, i- 2);j++) 
		{
			sum += getRombergFuntion(a+(2*j -1)*h)*h;
		}
		R[i][1] = 0.5*R[i - 1][1] + sum;
		for (int  k = 2; k <= i; k++)
		{
			R[i][k] = (pow(4, k - 1)*R[i][k-1]-R[i-1][k-1])/(pow(4,k-1)-1);
		}
	}

	for (int  i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << R[i][j] << " ";
		}
		cout << endl;
	}
}


int main()
{
	//测试数据求lnx在区间[1,2]上的积分，并输出四行lnx积分的数据
	getRombergValue(1,2,4);
	system("pause");
	return 0;
}