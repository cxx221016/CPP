#include <iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<cmath>
#include<unordered_set>
#include<cmath>
#include<functional>
using namespace std;


const double PI = acos(-1);
const double GEN = pow(2, -0.5);

inline void readQ(vector<vector<int>>& Q)
{
	for (auto&& Qline : Q)
	{
		for (auto&& q : Qline)
		{
			cin >> q;
		}
	}
}

inline void readM(vector<vector<int>>& M, int n)
{
	int dir = 0;
	int i = 0, j = 0;
	auto r = [&]()
	{
		cin >> M[i][j];
		if (i == 0&& j!=7)
		{
			j++;
			dir = !dir;
		}
		else if (j == 7 && i != 0)
		{
			i++;
			dir = !dir;
		}
		else
		{
			i--;
			j++;
		}
		//cout << i << " " << j <<" "<<dir<< endl;
	};

	auto l = [&]()
	{
		cin >> M[i][j];
		if (i == 7 )
		{
			j++;
			dir = !dir;
		}
		else if (j == 0)
		{
			i++;
			dir = !dir;
		}
		else
		{
			i++;
			j--;
		}
		//cout << i << " " << j << " " << dir << endl;
	};

	unordered_map<int, function<void()>> funmp
	{
		{0,r},
		{1,l}
	};
    
	while (n--)
	{
		funmp[dir]();
	}
}

void mul(vector<vector<int>>& M, const  vector<vector<int>>& Q)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			M[i][j] = M[i][j] * Q[i][j];
		}
	}
}

template<typename T>
void display(const vector<vector<T>>& M)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
}

void DCT(vector<vector<double>>& M_, vector<vector<int>>& M)
{
	auto cal = [&](int x, int y)->double
	{
		double res = 0.0;
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				res += 0.25 * (i == 0 ? GEN : 1) * (j == 0 ? GEN : 1) * M[i][j] * cos(0.125 * PI * (x + 0.5) * i) * cos(0.125 * PI * (y + 0.5) * j);
			}
		}
		return res;


	};
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			M_[i][j] = cal(i,j);
		}
	}
    //display(M_);

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			int res = round(M_[i][j] + 128);
			M[i][j] = res > 255 ? 255 : res < 0 ? 0 : res;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	vector<vector<int>> Q(8, vector<int>(8, 0)), M(8, vector<int>(8, 0));
	readQ(Q);
	int n, T;
	cin >> n >> T;
	readM(M,n);
    if (T == 0)
    {
        display(M);
        system("pause");
		return 0;
    }
	mul(M, Q);
	if (T == 1)
	{
        display(M);
        system("pause");
		return 0;
	}
	vector<vector<double>> M_(8, vector<double>(8, 0));
	DCT(M_, M);
	display(M);
    system("pause");
	return 0;

}