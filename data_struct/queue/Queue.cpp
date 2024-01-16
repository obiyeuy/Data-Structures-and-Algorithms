#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *initQueue()
{
    Node *Q = (Node *)malloc(sizeof(Node));
    Q->data = 0;
    Q->next = NULL;
    return Q;
}

int isEmpty(Node *Q)
{
    if (Q->data == 0 || Q->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enQueue(Node *Q, int data)
{
    Node *q = Q;
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    for (int i = 0; i < Q->data; ++i)
    {
        q = q->next;
    }
    q->next = node;
    Q->data++;
}

int deQueue(Node *Q)
{
    if (isEmpty(Q))
    {
        return -1;
    }
    else
    {
        Node *node = Q->next;
        int data = node->data;
        Q->next = node->next;
        Q->data--;
        free(node);
        return data;
    }
}

void printQueue(Node *Q)
{
    Node *node = Q->next;
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main()
{
    Node *Q = initQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);
    enQueue(Q, 5);
    printQueue(Q);
    printf("\n%d\n", Q->data);
    printf("%d\n", deQueue(Q));
    printf("%d\n", Q->data);
    printQueue(Q);
    return 0;
}