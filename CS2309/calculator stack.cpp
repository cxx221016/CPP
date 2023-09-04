#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<string>
#include<unordered_map>
#include<cmath>
using namespace std;


class Solution {
public:
    int calculate(string s) {
        trim(s);
        mid2post(s);
        return post2res();
    }
private:
    vector<string> postfix;
    stack<char> opStk;
    unordered_map<char, int> getPr{{'(', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},{'%',2}};
    void trim(string& s){ // 将'(-'转换为'(0-'，避免特殊情况讨论
        int i = 0;
        for (char j : s)
            if (j != ' ') s[i++] = j;
        s.resize(i);
        int pos = s.find("(-");
        while(pos != -1){
            s.replace(pos, 2, "(0-");
            pos = s.find("(-");
        }
    }
    void mid2post(string s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (isdigit(s[i])) { //当前是数字
                string curNum;
                while (i < n && (isdigit(s[i])))
                    curNum += s[i++];
                i--;
                postfix.push_back(curNum);
            }
            else if (s[i]=='(') opStk.push('('); //当前是左括号
            else if (s[i]==')'){ //当前是右括号
                while(!opStk.empty() && opStk.top()!='('){
                    postfix.push_back(string(1, opStk.top()));
                    opStk.pop();
                }
                opStk.pop(); //左括号也要弹出来
            }
            else { //当前是 + - * / %这些符号
                // 维护一个严格单调递增栈opStk，对于不比当前符号优先级高的，可以加入后缀表达式直接计算
                while (!opStk.empty() && getPr[opStk.top()] >= getPr[s[i]]) {
                    postfix.push_back(string(1, opStk.top()));
                    opStk.pop();
                }
                opStk.push(s[i]); 
            }
        }
        while (!opStk.empty()) {
            postfix.push_back(string(1, opStk.top()));
            opStk.pop();
        }
    }
    int post2res() {
        stack<int> numStk;
        numStk.push(0);
        for (string& cur : postfix) {
            if (isdigit(cur[0])) numStk.push(stoi(cur));
            else {
                int num2 = numStk.top(); numStk.pop();
                int num1 = numStk.top(); numStk.pop();
                switch (cur[0]) {
                    case '+': numStk.push(num1 + num2); break;
                    case '-': numStk.push(num1 - num2); break;
                    case '*': numStk.push(num1 * num2); break;
                    case '/': numStk.push(num1 / num2); break;
                    case '%': numStk.push(num1 % num2);
                }
            }
        }
        return numStk.top();
    }
};


int main()
{
    string s;
    cin>>s;
    Solution S;
    cout<<S.calculate(s);
    
    
    system("pause");
    return 0;
}