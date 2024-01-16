#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *initL()
{
    Node *L = (Node *)malloc(sizeof(Node));
    L->data = 0;
    L->next = L;
    return L;
}

// 头插法
void headInsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = L->next;
    L->next = node;
    L->data++;
}

// 尾插法
void tailInsert(Node *L, int data)
{
    Node *temp = L;
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = L;
    while (temp->next != L)
    {
        temp = temp->next;
    }
    temp->next = node;
    L->data++;
}

// 删除
int deleteL(Node *L, int data)
{
    Node *pre = L;
    Node *current = L->next;
    while (current != L)
    {
        if (current->data == data)
        {
            pre->next = current->next;
            free(current);
            L->data--;
            return TRUE;
        }
        else
        {
            pre = current;
            current = current->next;
        }
    }
    return FALSE;
}

// 遍历
void printL(Node *L)
{
    Node *node = L->next;
    while (node != L)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main()
{
    Node *L = initL();
    tailInsert(L, 6);
    tailInsert(L, 7);
    tailInsert(L, 8);
    tailInsert(L, 9);
    tailInsert(L, 10);
    printf("%d\n",L->data);
    headInsert(L, 1);
    headInsert(L, 2);
    headInsert(L, 3);
    headInsert(L, 4);
    headInsert(L, 5);
    printf("%d\n",L->data);
    printf("%d\n", deleteL(L, 5));
    printf("%d\n", deleteL(L, 10));
    printf("%d\n", deleteL(L, 10));
    printL(L);
    return 0;
}
