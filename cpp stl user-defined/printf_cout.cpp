#include<cstdio>
#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

typedef int teacher;

struct student
{
    string name;
    int age;
    float score;
    teacher* t;
};

enum Style
{
    C,
    Cpp
};

void print(student* s,Style style)
{
    if(style == C)
    {
        printf("name: %-20s age: %-3d score: %4.3f teacher: %#x\n",s->name.c_str(),s->age,s->score,s->t);
    }
    else if(style == Cpp)
    {
        cout << "name: " << setw(20) << left << s->name << " age: " << setw(3) << left << s->age << " score: " << setw(4) << left << setprecision(5)<< s->score << " teacher: " << s->t << endl;
    }
}

int main()
{
    teacher t(4);
    student s = {"zhangsan",20,99.9393883,&t};
    print(&s,C);
    print(&s,Cpp);
    system("pause");
    return 0;
}