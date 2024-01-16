#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 6
//循环队列长度为MAXSIZE-1

typedef struct Queue
{
    int front;
    int rear;
    int data[MAXSIZE];
} Queue;

Queue *initQueue()
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->front = Q->rear = 0;
    return Q;
}

//注意判断空和满的条件!!!
int isFull(Queue *Q)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty(Queue *Q)
{
    if (Q->front == Q->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int enQueue(Queue *Q, int data)
{
    if (isFull(Q))
    {
        return 0;
    }
    else
    {
        Q->data[Q->rear] = data;
        Q->rear = (Q->rear + 1) % MAXSIZE;
        return 1;
    }
}

int deQueue(Queue *Q)
{
    if (isEmpty(Q))
    {
        return -1;
    }
    else
    {
        int data = Q->data[Q->front];
        Q->front = (Q->front + 1) % MAXSIZE;
        return data;
    }
}

//重要!!!!!
void printQueue(Queue *Q) 
{
    int length= (Q->rear-Q->front+MAXSIZE)%MAXSIZE;
    int index=  Q->front;
    for(int i = 0;i<length;i++){
        printf("%d ",Q->data[index]);
        index = (index+1)%MAXSIZE;
    }
}
int main(){
    Queue* Q = initQueue();
    enQueue(Q,1);
    enQueue(Q,2);
    enQueue(Q,3);
    enQueue(Q,4);
    printf("%d %d\n",Q->front,Q->rear);
    enQueue(Q,5);
    printf("%d %d\n",Q->front,Q->rear);
    printQueue(Q);
    deQueue(Q);
    deQueue(Q);
    enQueue(Q,6);
    enQueue(Q,7);
    printf("\n%d %d\n",Q->front,Q->rear);
    enQueue(Q,8);
    printf("%d %d\n",Q->front,Q->rear);
    printQueue(Q);
    return 0;
}