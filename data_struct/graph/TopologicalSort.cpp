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

typedef struct StackNode{
    int data;
    struct StackNode* next;
}StackNode;

StackNode* initStack(){
    StackNode* stack =(StackNode*)malloc(sizeof(StackNode));
    stack->data = 0;
    stack->next = NULL;
    return stack;
}

void push(StackNode* S,int data){
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = data;
    node->next = S->next;
    S->next = node;
    S->data++;
}

int isEmpty(StackNode* S){
    if(S->next==NULL){
        return 1;
    }else{
        return 0;
    }
}

int pop(StackNode* S){
    if(isEmpty(S)){
        return -1;
    }else{
        StackNode* node = S->next;
        S->next = node->next;
        int data = node->data;
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

int* findInDegrees(Graph* G){
    int* inDegrees = (int*)malloc(sizeof(int)*G->vexNum);
    for(int i = 0;i<G->vexNum;i++){
        inDegrees[i] =0;
    }
    for(int i = 0;i<G->vexNum;i++){
        for(int j = 0;j<G->vexNum;j++){
            if(G->arcs[i][j]){
                inDegrees[j]++; 
            }
        }
    }
    return inDegrees;
}

void topologicalSort(Graph* G){
    int index;
    int* top = (int*)malloc(sizeof(int)*G->vexNum);
    int* inDegrees = findInDegrees(G);
    StackNode* S = initStack();
    for(int i = 0;i<G->vexNum;i++){
        if(inDegrees[i] == 0){
            push(S,i);
        }
    }
    while(!isEmpty(S)){
        int vex= pop(S);
        top[index++] = vex;
        for(int i = 0;i<G->vexNum;i++){  //将相关点的入度减一
            if(G->arcs[vex][i]){
                inDegrees[i]--;
                if(inDegrees[i] == 0){
                    push(S,i);
                }
            }
        }
    }

    for(int  i =0;i<G->vexNum;i++){
        printf("%c ",G->vexs[top[i]]);
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
