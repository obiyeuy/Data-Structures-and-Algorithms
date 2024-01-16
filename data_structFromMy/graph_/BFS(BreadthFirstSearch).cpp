#include <stdlib.h>
#include <stdio.h>

typedef struct Graph
{
    int **arcs;
    char *vexs;
    int vexnum;
    int arcnum;
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

void enQueue(QueueNode *Q, int data)
{
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    QueueNode *tmp = Q;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = node;
    Q->data++;
}

int isEmpty(QueueNode *Q)
{
    if (Q->data == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int deQueue(QueueNode *Q)
{
    if (isEmpty(Q))
    {
        return -1;
    }
    else
    {
        QueueNode *tmp = Q->next;
        Q->next = tmp->next;
        return tmp->data;
    }
}

Graph *initGraph(int vexnum)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->vexs = (char *)malloc(sizeof(char) * vexnum);
    G->arcs = (int **)malloc(sizeof(int *) * vexnum);
    G->vexnum = vexnum;
    for (int i = 0; i < G->vexnum; i++)
    {
        G->vexs[i] = 0;
        G->arcs[i] = (int *)malloc(sizeof(int) * G->vexnum);
        for (int j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j] = 0;
        }
    }
    return G;
}

void createGraph(Graph *G, char *vexs, int *arcs)
{
    for (int i = 0; i < G->vexnum; i++)
    {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j] = *(arcs + i * G->vexnum + j); // 二维数组中用列指针只能这样赋值
            if (G->arcs[i][j] != 0)
            { // i*G->vexNum是移动i行    j是移动j列
                G->arcnum++;
            }
        }
    }
    G->arcnum /= 2;
}

void BFS(Graph *G, int index, int *visited)
{
    QueueNode *Q = initQueue();
    printf("%c ", G->vexs[index]);
    enQueue(Q, index);
    while (!isEmpty(Q))
    {
        int i = deQueue(Q);
        for (int j = 0; j < G->vexnum; j++)
        {
            if (G->arcs[i][j] > 0 && visited[j] == 0)
            {
                printf("%c ", G->vexs[j]);
                visited[j] = 1;
                enQueue(Q, j);
            }
        }
    }
}

int main()
{
    Graph *G = initGraph(5);
    int *visited = (int *)malloc(sizeof(int) * G->vexnum);
    for (int i = 0; i < G->vexnum; i++)
    {
        visited[i] = 0;
    }
    int arcs[5][5] = {
        0, 1, 1, 1, 0,
        1, 0, 1, 1, 1,
        1, 1, 0, 0, 0,
        1, 1, 0, 0, 1,
        0, 1, 0, 1, 0};
    // createGraph(G,"ABCDE",(int*)arcs);    //两种一样
    createGraph(G, "ABCDE", *arcs);
    BFS(G, 0, visited);
    return 0;
}