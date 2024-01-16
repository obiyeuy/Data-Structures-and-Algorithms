// 有向无环图：DAG(描述工程或任务的子任务间的依赖关系)
// AOV网：1.图的节点表示任务 2.图的弧表示先后依赖关系   DAG就是一个AOV网
// 拓扑排序就是将AOV中的顶点排成一个线性序列，如果vi->vj有弧的话，那么vi必然在vj前面
// 拓扑排序一般用于判断是否有环
// 流程：
// 1.找出没有前驱的点，输出它，剪掉以它为出发点的所有边
// 2.重复第一步，直到图中不存在没有前驱的点

// 需要知道各顶点的入度

#include<stdlib.h>
#include<stdio.h>

#define MAX 32767

typedef struct Graph{
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
}Graph;

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

Graph* initGraph(int vexNum){
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->vexs = (char*)malloc(sizeof(char)*vexNum);
    G->arcs = (int**)malloc(sizeof(int*)*vexNum);
    for(int i = 0;i<vexNum;i++){
        G->arcs[i] = (int*)malloc(sizeof(int)*vexNum);
    }
    G->vexNum = vexNum;
    G->arcNum = 0;
    return G;
}

void createGraph(Graph* G,char* vexs,int* arcs){
    for(int i =0;i<G->vexNum;i++){
        G->vexs[i] = vexs[i];
        for(int j = 0;j<G->vexNum;j++){
            G->arcs[i][j] = *(arcs+i*G->vexNum+j);
            if(G->arcs[i][j]!=0){
                G->arcNum++;
            }
        }
    }
    G->arcNum /=2;
}

void DFS(Graph* G,int* visited,int index){
    printf("%c ",G->vexs[index]);
    visited[index] = 1;
    for(int i = 0;i<G->vexNum;i++){
        if(G->arcs[index][i] == 1 && !visited[i]){  //两点之间有边(不为0与MAX)且没被访问过
            DFS(G,visited,i);
        }
    }
}


void topologicalSort(Graph* G){
    int* inDegrees = (int*)malloc(sizeof(int)*G->vexNum);
    for(int i = 0;i<G->vexNum;i++){
        inDegrees[i] = 0;
    }
    for(int i = 0;i<G->vexNum;i++){
        for(int j = 0;j<G->vexNum;j++){
            if(G->arcs[i][j]!=0 && G->arcs[i][j] !=MAX){
                inDegrees[j]++;
            }
        }
    }

    int* result = (int*)malloc(sizeof(int)*G->vexNum);
    QueueNode* Q = initQueue();
    for(int i = 0;i<G->vexNum;i++){
        if(inDegrees[i] == 0){
            enQueue(Q,i);
        }
    }
    int index = 0;
    while(!isEmpty(Q)){
        int vex = deQueue(Q);
        result[index] = vex;
        index++;
        for(int i = 0;i<G->vexNum;i++){
            if(G->arcs[vex][i]!=0 && G->arcs[vex][i] !=MAX){
                inDegrees[i]--;
                if(inDegrees[i] == 0){  //不要忘了将变为0的顶点入队
                    enQueue(Q,i);
                }
            }
        }
    }

    for(int  i =0;i<G->vexNum;i++){
        printf("%c ",G->vexs[result[i]]);
    }
}

int main() {
    Graph* G = initGraph(6);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++){
        visited[i] = 0;
    }
    int arcs[6][6] = {
            0,1,1,1,0,0,
            0,0,0,0,0,0,
            0,1,0,0,1,0,
            0,0,0,0,1,0,
            0,0,0,0,0,0,
            0,0,0,1,1,0
    };
    createGraph(G, "ABCDEF", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    topologicalSort(G);
    return 0;
}
