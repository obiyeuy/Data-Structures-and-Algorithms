// AOE(Activity on Edge)网：事件就是顶点  活动就是弧
// 估算工程完成时间或者判断哪些活动是完成工程的关键
// 1.先拓扑排序
// 2.计算指标：事件指标：最早开始时间  最晚开始时间   活动指标：最早开始时间  最晚开始时间   时间余量(最晚减最早)为0时这个活动就是关键活动
// 3.找出关键活动

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
            if(G->arcs[i][j]>0 && G->arcs[i][j] !=MAX){
                G->arcNum++;
            }
        }
    }
}

void DFS(Graph* G,int* visited,int index){
    printf("%c ",G->vexs[index]);
    visited[index] = 1;
    for(int i = 0;i<G->vexNum;i++){
        if(G->arcs[index][i] >0 && G->arcs[index][i] !=MAX&& !visited[i]){  
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
            if(G->arcs[i][j]>0 && G->arcs[i][j]!=MAX){
                inDegrees[j]++; 
            }
        }
    }
    return inDegrees;
}

int* topologicalSort(Graph* G){
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
            if(G->arcs[vex][i]>0 && G->arcs[vex][i]!=MAX){
                inDegrees[i]--;
                if(inDegrees[i] == 0){
                    push(S,i);
                }
            }
        }
    }
    // printf("拓扑排序结果:\n");
    for(int i  =0;i<G->vexNum;i++){
        printf("%d ",top[i]);
    }
    printf("\n");
    return top;
}

int getIndex(int* top,Graph* G,int i){
    int j;
    for(j = 0;j<G->vexNum;j++){
        if(top[j] == i){
            break;
        }
    }
    return j;
}

void criticalPath(Graph* G){
    int* top = topologicalSort(G);
    int* early = (int*)malloc(sizeof(int)*G->vexNum);
    int* late = (int*)malloc(sizeof(int)*G->vexNum);
    for(int i = 0;i<G->vexNum;i++){
        early[i] = 0;
        late[i] = 0;
    }
    //计算最早发生时间
    for(int i = 0;i<G->vexNum;i++){
        int max = 0;
        for(int j = 0;j<G->vexNum;j++){
            if(G->arcs[j][top[i]]>0&&G->arcs[j][top[i]]!=MAX){
                int index = getIndex(top,G,j);
                if(early[index]+G->arcs[j][top[i]]>max){
                    max= early[index]+G->arcs[j][top[i]];
                }
            }
        }
        early[i] = max;
    }
    // printf("事件最早完成时间:\n");
    for(int i  =0;i<G->vexNum;i++){
        printf("%d ",early[i]);
    }
    printf("\n");
    late[(G->vexNum)-1] = early[(G->vexNum)-1];
    for(int i = (G->vexNum)-2;i>=0;i--){
        int min = MAX;
        for(int j =0;j<G->vexNum;j++){
            if(G->arcs[top[i]][j]>0 && G->arcs[top[i]][j] !=MAX){
                int index = getIndex(top,G,j);
                if(late[index] - G->arcs[top[i]][j]<min){
                    min = late[index] - G->arcs[top[i]][j];
                }
            }
        }
        late[i] = min;
    }
    // printf("事件最晚完成时间:\n");
    for(int i  =0;i<G->vexNum;i++){
        printf("%d ",late[i]);
    }
    printf("\n");
    // 关键路径输出
    for(int i = 0;i<G->vexNum;i++){
        for(int j =0;j<G->vexNum;j++){
            if(G->arcs[i][j]>0&&G->arcs[i][j]!=MAX){
                int start = getIndex(top,G,i);
                int end = getIndex(top,G,j);
                if(late[end]-G->arcs[i][j] == early[start]){
                    printf("start=%d end=%d\n",i,j);
                }
            }
        }
    }
}

int main() {
    Graph* G = initGraph(9);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++){
        visited[i] = 0;
    }
    int arcs[9][9] = {
            0,6,4,5,MAX,MAX,MAX,MAX,MAX,
            MAX,0,MAX,MAX,1,MAX,MAX,MAX,MAX,
            MAX,MAX,0,MAX,1,MAX,MAX,MAX,MAX,
            MAX,MAX,MAX,0,MAX,2,MAX,MAX,MAX,
            MAX,MAX,MAX,MAX,0,MAX,9,7,MAX,
            MAX,MAX,MAX,MAX,MAX,0,MAX,4,MAX,
            MAX,MAX,MAX,MAX,MAX,MAX,0,MAX,2,
            MAX,MAX,MAX,MAX,MAX,MAX,MAX,0,4,
            MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX,0
    };
    createGraph(G, "012345678", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    criticalPath(G);
    return 0;
}



