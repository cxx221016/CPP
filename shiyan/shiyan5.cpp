#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>
#include <set>
#include <type_traits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <optional>
#include <thread>
#include <iomanip>
#include <list>
#include <cstring>
#include <cctype>
#include <cmath>
// #include"json.hpp"
using namespace std;

struct Matrix
{
    std::vector<std::vector<long long int>> data;
    Matrix(std::initializer_list<long long int> list)
    {
        if (list.size() != 4)
        {
            throw std::invalid_argument("invalid initializer list");
        }
        data.emplace_back(std::vector<long long int>{*list.begin(), *(list.begin() + 1)});
        data.emplace_back(std::vector<long long int>{*(list.begin() + 2), *(list.begin() + 3)});
    }
    Matrix(long long int lu = 0, long long int ru = 0, long long int ld = 0, long long int rd = 0)
    {
        data.emplace_back(std::vector<long long int>{lu, ru});
        data.emplace_back(std::vector<long long int>{ld, rd});
    }

    static Matrix identity()
    {
        return Matrix(1, 0, 0, 1);
    }
    inline static int mod = 1000000007;
    Matrix power(int n)
    {
        Matrix res = identity();
        Matrix a = *this;
        while (n)
        {
            if (n & 1)
            {
                res *= a;
            }
            a *= a;
            n >>= 1;
        }
        return res;
    }
    Matrix operator*(const Matrix &rhs)
    {
        Matrix res;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                res.data[i][j] = ((data[i][0] % mod + mod) % mod * (rhs.data[0][j] % mod + mod) % mod + (data[i][1] % mod + mod) % mod * (rhs.data[1][j] % mod + mod) % mod) % mod;
            }
        }
        return res;
    }
    Matrix &operator*=(const Matrix &rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mtx)
    {
        os << mtx.data[0][0] << " " << mtx.data[0][1] << std::endl;
        os << mtx.data[1][0] << " " << mtx.data[1][1] << std::endl;
        return os;
    }
};

std::vector<std::pair<std::string, std::string>> solve(const int &base)
{
    std::vector<std::pair<std::string, std::string>> res;
    auto getstr = [&](int n)
    {
        std::string s;
        while (n)
        {
            auto curmod = n % base;
            if (curmod >= 10)
            {
                s.push_back(curmod - 10 + 'A');
            }
            else
            {
                s.push_back(curmod + '0');
            }
            n /= base;
        }
        std::reverse(s.begin(), s.end());
        return s;
    };

    for (int i = 1; i <= 200; i++)
    {
        auto ps = getstr(i);
        auto s = getstr(i * i);
        auto s2 = s;
        std::reverse(s2.begin(), s2.end());
        if (s == s2)
        {
            res.emplace_back(std::make_pair(ps, s));
        }
    }
    return res;
}

int main()
{
    while (true)
    {

        vector<int> nums = {2, 3, 4, 5};
        int goal_num;
        cin >> goal_num;
        vector<int> goal;
        while (goal_num)
        {
            goal.push_back(goal_num % 10);
            goal_num /= 10;
        }
        reverse(goal.begin(), goal.end());
        int n = goal.size();
        function<int(int, bool)> back = [&](int idx, bool preEq)
        {
            if (idx == n)
            {
                return 0;
            }
            if (preEq)
            {
                for (int i = nums.size() - 1; i >= 0; --i)
                {
                    if (idx == n - 1)
                    {
                        if (nums[i] < goal[idx])
                        {
                            return nums[i];
                        }
                    }
                    else
                    {
                        if (nums[i] <= goal[idx])
                        {
                            int temp = back(idx + 1, nums[i] == goal[idx]);
                            if (temp == -1)
                                continue;
                            return int(nums[i] * pow(10, n - idx - 1) + temp);
                        }
                    }
                }
                if (idx == 0)
                {
                    return back(idx + 1, false);
                }
                return -1;
            }
            else
            {
                return int(nums.back() * pow(10, n - idx - 1) + back(idx + 1, false));
            }
        };

        cout << back(0, true) << endl;
    }
    system("pause");
    return 0;
}
