#include<stdio.h>
#include<stdlib.h>

typedef struct Graph{
    char* vexs;  //顶点
    int** arcs;  //边(以邻接矩阵的方式存储)
    int vexNum;  //顶点数
    int arcNum;  //边数
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
        G->arcs[i] =  (int*)malloc(sizeof(int)*vexNum);
    }
    G->vexNum = vexNum;
    G->arcNum = 0;
    return G;
}

//需传入顶点数组(char* vexs)与边数组的列指针
void createGraph(Graph* G,char* vexs,int* arcs){
    for(int i = 0;i<G->vexNum;i++){
        G->vexs[i] = vexs[i];
        for(int j = 0;j<G->vexNum;j++){
            G->arcs[i][j] = *(arcs+i*G->vexNum+j);   //二维数组中用列指针只能这样赋值  
            if(G->arcs[i][j]!=0){        // i*G->vexNum是移动i行    j是移动j列
                G->arcNum++;
            }                                        
        }
    }
    G->arcNum /=2;
}

//图的遍历
// DFS:深度优先遍历
//1.找一个节点
//2.找这个节点可以访问的节点
//3.重复第一步，直到没有节点
void DFS(Graph* G,int* visited,int index){
    printf("%c ",G->vexs[index]);
    visited[index] = 1;
    for(int i =0;i<G->vexNum;i++){
        if(G->arcs[index][i] == 1 && !visited[i]){
            DFS(G,visited,i);
        }
    }
}
// BFS:广度优先遍历(与树的层序遍历类似)
void BFS(Graph* G,int* visited,int index){
    QueueNode* Q = initQueue();
    printf("%c ",G->vexs[index]);
    visited[index] = 1;
    enQueue(Q,index);
    while(!isEmpty(Q)){
        int i = deQueue(Q);
        for(int j = 0;j<G->vexNum;j++){
            if(G->arcs[i][j] == 1 && !visited[j]){
                printf("%c ",G->vexs[j]);
                visited[j] = 1;
                enQueue(Q,j);
            }
        }
    }
}


int main(){
    Graph* G = initGraph(5);
    int* visited = (int*)malloc(sizeof(int)*G->vexNum);
    for(int i  =0;i<G->vexNum;i++){
        visited[i] = 0;
    }
    int arcs[5][5] = {
        0,1,1,1,0,
        1,0,1,1,1,
        1,1,0,0,0,
        1,1,0,0,1,
        0,1,0,1,0
    };
    // createGraph(G,"ABCDE",(int*)arcs);    //两种一样
    createGraph(G,"ABCDE",*arcs);
    DFS(G,visited,0);
    printf("\n");
    for(int i  =0;i<G->vexNum;i++){
        visited[i] = 0;
    }
    BFS(G,visited,0);
    return 0;
}