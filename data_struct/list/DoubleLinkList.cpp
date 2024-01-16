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
    L->pre = NULL;
    L->next = NULL;
    return L;
}

// 头插法
void headInsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    if (L->data == 0)
    {
        // 链表为空
        node->next = NULL;
        node->pre = L;
        L->next = node;
    }
    else
    {
        node->pre = L;
        node->next = L->next;
        L->next->pre = node;
        L->next = node;
    }
    L->data++;
}

// 尾插法
void tailInsert(Node *L, int data)
{
    Node *head = L;
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    while (L->next)
    {
        L = L->next;
    }
    L->next = node;
    node->pre = L;
    head->data++;
}

// 删除
void deleteList(Node *L, int data)
{
    // Node *pre = L;
    Node *current = L->next;
    while (current)
    {
        if (current->data == data)
        {
            if (current->next == NULL)
            {
                current->pre->next = NULL;
            }
            else
            {
                current->pre->next = current->next;
                current->next->pre = current->pre;
            }
            free(current);
            break;
        }
        else
        {
            // pre = current;
            current = current->next;
        }
    }
    L->data--;
}

// 遍历
void printList(Node *L)
{
    L = L->next;
    while (L)
    {
        printf("%d ", L->data);
        L = L->next;
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
    headInsert(L, 1);
    headInsert(L, 2);
    headInsert(L, 3);
    headInsert(L, 4);
    headInsert(L, 5);
    printf("%d\n",L->data);
    deleteList(L, 10);
    deleteList(L, 5);
    printf("%d\n",L->data);
    printList(L);
    return 0;
}
