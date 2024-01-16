#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef struct StackNode
{
    char data;
    struct StackNode *next;
} StackNode;

StackNode *initStack()
{
    StackNode *S = (StackNode *)malloc(sizeof(StackNode));
    S->data = 0;
    S->next = NULL;
    return S;
}

int isEmpty(StackNode *S)
{
    if (S->data == 0 || S->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(StackNode *S, char data)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->data = data;
    node->next = S->next;
    S->next = node;
    S->data++;
}

char pop(StackNode *S)
{
    if (isEmpty(S))
    {
        return 0;
    }
    else
    {
        StackNode *node = S->next;
        S->next = node->next;
        S->data--;
        return node->data;
    }
}

void printStack(StackNode *S)
{
    StackNode *node = S->next;
    while (node)
    {
        printf("%c", node->data);
        node = node->next;
    }
}

void zhuanhuan(int num, int jzhi)
{
    StackNode *S = initStack();
    int tmp;
    switch (jzhi)
    {
    case 2:
    case 8:
        while (num > 0)
        {
            tmp = num % jzhi;
            push(S, (char)tmp);
            num /= jzhi;
        }
        printStack(S);
        break;
    case 16:
        while(num>0){
            tmp = num%jzhi;
            if(tmp==10)
				push(S,'A');
			else if(tmp==11)
				push(S,'B');
			else if(tmp==12)
				push(S,'C');
			else if(tmp==13)
				push(S,'D');
			else if(tmp==14)
				push(S,'E');
			else if(tmp==15)
				push(S,'F');
			else push(S,tmp);
            push(S, (char)tmp);
            num /= jzhi;
        }
        printStack(S);
        break;
    }
}
int main()
{
    int num = 0;
    scanf("%d", &num);
    int jzhi = 0;
    scanf("%d", &jzhi);
    zhuanhuan(num,jzhi);
}
