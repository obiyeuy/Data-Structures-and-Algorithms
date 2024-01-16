// #include<bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

struct Node
{
    string id;
    string name;
    int grade;
};

void sort_id(Node *&S, int num)
{
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = 0; j < num - 1 - i; j++)
        {
            if (S[j].id > S[j + 1].id)
            {
                Node tmp = S[j + 1];
                S[j + 1] = S[j];
                S[j] = tmp;
            }
        }
    }
}

void sort_name(Node *&S, int num)
{
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = 0; j < num - 1 - i; j++)
        {
            if (S[j].name > S[j + 1].name)
            {
                Node tmp = S[j + 1];
                S[j + 1] = S[j];
                S[j] = tmp;
            }
            else if (S[j].name == S[j + 1].name)
            {
                if (S[j].id > S[j + 1].id)
                {
                    Node tmp = S[j + 1];
                    S[j + 1] = S[j];
                    S[j] = tmp;
                }
            }
        }
    }
}

void sort_grade(Node *&S, int num)
{
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = 0; j < num - 1 - i; j++)
        {
            if (S[j].grade > S[j + 1].grade)
            {
                Node tmp = S[j + 1];
                S[j + 1] = S[j];
                S[j] = tmp;
            }
            else if (S[j].grade == S[j + 1].grade)
            {
                if (S[j].id > S[j + 1].id)
                {
                    Node tmp = S[j + 1];
                    S[j + 1] = S[j];
                    S[j] = tmp;
                }
            }
        }
    }
}

int main()
{

    int num, operate;
    cin >> num >> operate;

    // 创建结构体数组
    Node *S = new Node[num];

    for (int i = 0; i < num; i++)
    {
        cin >> S[i].id >> S[i].name >> S[i].grade;
    }

    switch (operate)
    {
    case 1:
        sort_id(S, num);
        break;
    case 2:
        sort_name(S, num);
        break;
    case 3:
        sort_grade(S, num);
        break;
    default:
        break;
    }
    for (int i = 0; i < num; i++)
    {
        cout << S[i].id << ' ' << S[i].name << ' ' << S[i].grade << endl;
    }
}
