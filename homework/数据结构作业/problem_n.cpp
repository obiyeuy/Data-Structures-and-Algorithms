#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX 100

typedef struct Graph
{
    int *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
} Graph;

typedef struct QueueNode
{
    int data;
    struct QueueNode *next;
} QueueNode;

QueueNode *initQueue()
{
    QueueNode *Q = (QueueNode *)malloc(sizeof(QueueNode));
    Q->data = 0;
    Q->next = NULL;
    return Q;
}

int isEmpty(QueueNode *Q)
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

void enQueue(QueueNode *Q, int data)
{
    QueueNode *q = Q;
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    for (int i = 0; i < Q->data; ++i)
    {
        q = q->next;
    }
    q->next = node;
    Q->data++;
}

int deQueue(QueueNode *Q)
{
    if (isEmpty(Q))
    {
        return -1;
    }
    else
    {
        QueueNode *node = Q->next;
        int data = node->data;
        Q->next = node->next;
        Q->data--;
        free(node);
        return data;
    }
}

Graph *initGraph(int vexNum, int arcNum)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->vexs = (int *)malloc(sizeof(int) * vexNum);
    G->arcs = (int **)malloc(sizeof(int *) * vexNum);
    for (int i = 0; i < vexNum; i++)
    {
        G->vexs[i] = i+1;
        G->arcs[i] = (int *)malloc(sizeof(int) * vexNum);
        for (int j = 0; j < vexNum; j++)
        {
            G->arcs[i][j] = 0;
        }
    }
    G->vexNum = vexNum;
    G->arcNum = arcNum;
    return G;
}

void createGraph(Graph *G)
{
    int left, right;
    int leftIndex, rightIndex;
    for (int i = 0; i < G->arcNum; i++)
    {
        cin >> left >> right;
        int count = 0;
        for (int j = 0; j < G->vexNum; j++)
        {
            if (left == G->vexs[j])
            {
                leftIndex = j;
                count++;
            }
            if (right == G->vexs[j])
            {
                rightIndex = j;
                count++;
            }
            if(count ==2){
                break;
            }
        }
        G->arcs[leftIndex][rightIndex] = 1;
        G->arcs[rightIndex][leftIndex] = 1;
    }
}


int BFS(Graph* G,int* visited,int index){
    int count = 0;
    QueueNode* Q = initQueue();
    count++;
    visited[index] = 1;
    enQueue(Q,index);
    while(!isEmpty(Q)){
        int i = deQueue(Q);
        for(int j = 0;j<G->vexNum;j++){
            if(G->arcs[i][j] == 1 && !visited[j]){
                count++;
                visited[j] = 1;
                enQueue(Q,j);
            }
        }
    }
    return count;
}

int main()
{
    int vexNum, arcNum;
    scanf("%d %d", &vexNum, &arcNum);
    Graph *G = initGraph(vexNum, arcNum);
    createGraph(G);
    // for(int i = 0;i<G->vexNum;i++){
    //     printf("%d\t",G->vexs[i]);
    //     for(int j = 0;j<G->vexNum;j++){
    //         printf("%d ",G->arcs[i][j]);
    //     }
    //     printf("\n");
    // }
    int *visited = (int *)malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; i++)
    {
        visited[i] = 0;
    }
    int num[MAX];
    int length = 0;
    int count = 0;
    for (int i = 0; i < G->vexNum; i++)
    {
        if (visited[i] == 0)
        {
            count = BFS(G, visited, i);
            if(count > 1){
                num[length] = count;
                length++;
            }
            count = 0;
        }
    }
    printf("%d\n",length);
    for(int i = 0;i<length-1;i++){
        for(int j = 0;j<length-1-i;j++){
            if(num[j]>num[j+1]){
                int tmp = num[j];
                num[j] = num[j+1];
                num[j+1] = tmp;
            }
        }
    }
    for(int i = 0;i<length;i++){
        printf("%d ",num[i]);
    }
    return 0;
}