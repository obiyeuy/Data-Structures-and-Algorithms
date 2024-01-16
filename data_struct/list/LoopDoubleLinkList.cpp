#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *pre;
    struct Node *next;
} Node;

Node *initList()
{
    Node *L = (Node *)malloc(sizeof(Node));
    L->data = 0;
    L->pre = L;
    L->next = L;
    return L;
}

// 头插法
void headInsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->pre = L;
    node->next = L->next;
    L->next->pre = node;
    L->next = node;
    L->data++;
}

// 尾插法
void tailInsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->pre = L->pre;
    node->next = L;
    L->pre->next = node;
    L->pre = node;
    L->data++;
}

// 删除
int deleteList(Node *L, int data)
{
    // Node *pre = L;
    Node *current = L->next;
    while (current != L)
    {
        if (current->data == data)
        {
            current->pre->next = current->next;
            current->next->pre = current->pre;
            free(current);
            L->data--;
            return 1;
        }
        else
        {
            current = current->next;
        }
    }
    return 0;
}

// 遍历
void printList(Node *L)
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
    Node *L = initList();
    tailInsert(L, 6);
    tailInsert(L, 7);
    tailInsert(L, 8);
    tailInsert(L, 9);
    tailInsert(L, 10);
    printf("%d\n", L->data);
    headInsert(L, 1);
    headInsert(L, 2);
    headInsert(L, 3);
    headInsert(L, 4);
    headInsert(L, 5);
    printf("%d\n", L->data);
    deleteList(L, 10);
    deleteList(L, 5);
    printList(L);
    return 0;
}
