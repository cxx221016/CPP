#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iomanip>
// #include "MyClass1.h"
// #include "MyClass2.h"

using namespace std;
class MyClass1
{
};
class MyClass2
{
};
class MyClass3
{
};
// 存储数组全局定义
int cinlen = 0, coutlen = 0;
unordered_map<string, int> NO;
vector<map<string, double>> A;
vector<double> B;
vector<string> TRUE;
vector<string> FALSE;

double keep(double x)
{
    int flag = x >= 0;
    if (flag)
        return floor(x * 10000.000f + 0.1) / 10000.000f;
    else
        return -(floor(abs(x) * 10000.000f + 0.1) / 10000.000f);
}

double accuracy = 0.00000000001;
double z = 0;

bool equal(double a)
{
    if (abs(a) <= accuracy)
        return 1;
    else
        return 0;
}

bool equal(double a, double b)
{
    if (abs(a - b) <= accuracy)
        return 1;
    else
        return 0;
}

void change(vector<vector<double>> &A, vector<double> &B)
{
    int n = A.size();
    unordered_set<int> seen;
    vector<vector<int>> dp(n);
    int index = A[0].size();
    for (int i = 0; i < n; ++i)
    {
        if (seen.count(i))
            continue;
        for (int j = i + 1; j < n; ++j)
        {
            if (seen.count(j))
                continue;
            if (B[i] * A[j][0] == A[i][0] * B[j])
            {
                bool flag = true;
                double dev = B[i] / B[j];
                for (int k = 1; k < index; ++k)
                {
                    if (B[i] * A[j][k] != A[i][k] * B[j])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    seen.insert(j);
                }
            }
        }
    }

    vector<vector<double>> cloneA;
    vector<double> cloneB;
    for (int i = 0; i < n; ++i)
    {
        if (!seen.count(i))
        {
            cloneA.push_back(A[i]);
            cloneB.push_back(B[i]);
        }
    }

    A.clear();
    B.clear();
    A = cloneA;
    B = cloneB;
}

void pre_dis()
{
    string str = "Legal Equations:";
    coutlen += str.size();
    for (auto &t : TRUE)
    {
        coutlen += 1 + t.size();
    }
}

void suf_dis()
{
    string str = "Illegal Equations:";
    coutlen += 1 + str.size();
    for (auto &f : FALSE)
    {
        coutlen += 1 + f.size();
    }
}

void pre_display()
{
    cout << cinlen << ":" << coutlen;
    cout << endl
         << "Legal Equations:";
    for (auto &t : TRUE)
    {
        cout << endl
             << t;
    }
}

void suf_display()
{
    cout << endl
         << "Illegal Equations:";
    for (auto &f : FALSE)
    {
        cout << endl
             << f;
    }
}

bool isvalid(string &str, vector<pair<string, double>> &init, double &b)
{
    int n = str.size();
    int i = 0;
    double isz = 1;
    unordered_set<string> seen;
    while (i < n)
    {
        char ch = str[i];
        if (isdigit(ch))
        {
            int j = i + 1;
            while (str[j] != '*')
            {
                if (isdigit(str[j]) || str[j] == '.')
                {
                    ++j;
                }
                else
                    return false;
            }
            double coef = stof(str.substr(i, j - i));
            string xyz;

            if (islower(str[++j]))
            {
                xyz += str[j];
            }
            else
                return false;

            j++;
            int cnt = 2;
            while (isdigit(str[j]))
            {
                cnt--;
                xyz += str[j];
                ++j;
            }
            if (cnt < 0)
                return false;
            init.push_back({xyz, isz * coef});
            isz = 1;
            i = j;
        }
        else if (islower(ch))
        {
            double coef = 1.0;
            string xyz;
            xyz += ch;
            int j = i + 1;
            int cnt = 2;
            while (isdigit(str[j]))
            {
                cnt--;
                xyz += str[j];
                ++j;
            }
            if (cnt < 0)
                return false;
            if (seen.count(xyz))
                return false;
            seen.insert(xyz);
            init.push_back({xyz, isz * coef});
            isz = 1;
            i = j;
        }
        else if (ch == '-')
        {
            isz = -1;
            i++;
        }
        else if (ch == '+')
        {
            isz = 1;
            i++;
        }
        else if (ch == '=')
        {
            int j = i + 1;
            double p = 1.0;
            if (str[j] == '-')
            {
                p = -1.0;
                ++j;
            }
            int begin = j;
            while (j < n)
            {
                if (isdigit(str[j]) || str[j] == '.')
                {
                    ++j;
                }
                else
                    return false;
            }
            b = p * stof(str.substr(begin));
            i = j;
        }
        else
            return false;
    }
    return true;
}

vector<double> compute(vector<vector<double>> &matrix, vector<double> &B)
{
    int variableNum = A.size();
    for (int i = 0; i < variableNum; ++i)
    {
        matrix[i].push_back(B[i]);
    }
    int nwline = 0;
    for (int k = 0; k < variableNum; ++k)
    {
        int maxi = nwline;
        for (int i = nwline + 1; i < variableNum; ++i)
        {
            if (abs(matrix[i][k]) > abs(matrix[maxi][k]))
                maxi = i;
        }
        if (abs(matrix[maxi][k]) < 1e-9)
            continue;
        for (int j = 0; j < variableNum + 1; ++j)
            swap(matrix[nwline][j], matrix[maxi][j]);
        for (int i = 0; i < variableNum; ++i)
        {
            if (i == nwline)
                continue;
            double mul = matrix[i][k] / matrix[nwline][k];
            for (int j = k + 1; j < variableNum + 1; ++j)
                matrix[i][j] -= matrix[nwline][j] * mul;
        }
        ++nwline;
    }

    if (nwline < variableNum)
    {
        while (nwline < variableNum)
        {
            if (matrix[nwline++][variableNum] != 0)
                throw MyClass1();
        }
        throw MyClass2();
    }
    int i = 0;
    vector<double> X;
    while (i < variableNum)
    {
        double tmp = matrix[i][variableNum] / matrix[i][i];
        X.push_back(tmp);
        i++;
    }
    return X;
}

// 请根据自己需求定义MyClass1和MyClass2
// 定义main函数
int main()
{
    /********** Begin **********/
    // 读取测试输入
    string str;
    while (cin)
    {
        str = "";
        getline(cin, str);
        cinlen += str.size() + 1;
        bool firflag = true;
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] == '.' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '=' || islower(str[i]) || isdigit(str[i]))
            {
            }
            else
            {
                firflag = false;
                break;
            }
        }

        if (!firflag)
        {
            FALSE.push_back(str);
            continue;
        }

        if (firflag)
        {
            vector<pair<string, double>> init;
            map<string, double> mp;
            double b = 0.0;

            if (isvalid(str, init, b))
            {
                TRUE.push_back(str);
                for (auto &ini : init)
                {
                    mp.insert(ini);
                }
                A.push_back(mp);
                B.push_back(b);
            }
            else
            {
                FALSE.push_back(str);
            }
        }
    }
    A.pop_back();
    B.pop_back();
    TRUE.pop_back();
    cinlen -= 2;
    pre_dis();
    suf_dis();
    // 请打印输出运算结果
    int n = A.size();
    int index = 0;
    set<string> seen;
    for (auto &a : A)
    {
        for (auto &entry : a)
        {
            if (!seen.count(entry.first))
            {
                seen.insert(entry.first);
            }
        }
    }

    for (auto &see : seen)
    {
        NO[see] = index++;
    }
    vector<vector<double>> DA(n, vector<double>(index, 0));
    try
    {
        if (index == 0 && n == 0)
            throw MyClass3();
        if (index > n)
            throw MyClass2();
        for (int i = 0; i < n; ++i)
        {
            auto a = A[i];
            for (auto &entry : a)
            {
                DA[i][NO[entry.first]] = entry.second;
            }
        }
        change(DA, B);
        n = DA.size();
        if (index < n)
            throw MyClass1();
        vector<double> result = compute(DA, B);
        coutlen += 8 * n;
        for (auto &see : seen)
        {
            coutlen += see.size();
        }
        for (auto &res : result)
        {
            coutlen += res < 0 ? 1 : 0;
        }
        pre_display();
        int i = 0;
        for (auto &see : seen)
        {
            cout << endl
                 << see << ":" << fixed << setprecision(4) << keep(result[i]);
            ++i;
        }
        suf_display();
    }
    catch (MyClass1 &m1)
    {
        coutlen += 7;
        pre_display();
        cout << endl
             << "error1";
        suf_display();
    }
    catch (MyClass2 &m2)
    {
        coutlen += 7;
        pre_display();
        cout << endl
             << "error2";
        suf_display();
    }

    catch (MyClass3 &m3)
    {
        pre_display();
        suf_display();
    }

    /********** End **********/
    system("pause");
    return 0;
}