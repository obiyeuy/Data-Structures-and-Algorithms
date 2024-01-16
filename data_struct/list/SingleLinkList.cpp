#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *initList()
{
    Node *list = (Node *)malloc(sizeof(Node));
    list->data = 0;
    list->next = NULL;
    return list;
}

// 头插法
void headInsert(Node *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = list->next;
    list->next = node;
    list->data++;
}

// 尾插法
void tailInsert(Node *list, int data)
{
    Node *head = list;
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    while (list->next)
    {
        list = list->next;
    }
    list->next = node;
    head->data++;
}

// 删除
void deleteList(Node *list, int data)
{
    Node *pre = list;
    Node *current = list->next;
    while (current)
    {
        if (current->data == data)
        {
            pre->next = current->next;
            free(current);
            break;
        }
        else
        {
            pre = current;
            current = current->next;
        }
    }
    list->data--;
}

// 遍历
void printList(Node *list)
{
    list = list->next;
    while (list)
    {
        printf("%d ", list->data);
        list = list->next;
    }
}

int main()
{
    Node *list = initList();
    tailInsert(list, 6);
    tailInsert(list, 7);
    tailInsert(list, 8);
    tailInsert(list, 9);
    tailInsert(list, 10);
    headInsert(list, 1);
    headInsert(list, 2);
    headInsert(list, 3);
    headInsert(list, 4);
    headInsert(list, 5);
    printf("%d\n",list->data);
    printList(list);
    return 0;
}
