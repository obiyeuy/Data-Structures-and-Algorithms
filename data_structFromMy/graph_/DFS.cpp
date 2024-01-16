#include<stdlib.h>
#include<stdio.h>

typedef struct Graph{
    int** arcs;
    char* vexs;
    int vexnum;
    int arcnum;
}Graph;

Graph* initGraph(int vexnum){
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->vexs = (char*)malloc(sizeof(char)*vexnum);
    G->arcs = (int**)malloc(sizeof(int*)*vexnum);
    G->vexnum = vexnum;
    for(int i = 0;i<G->vexnum;i++){
        G->vexs[i] = 0;
        G->arcs[i] = (int*)malloc(sizeof(int)*G->vexnum);
        for(int j= 0;j<G->vexnum;j++){
            G->arcs[i][j] = 0;
        }
    }
    return G;
}


void createGraph(Graph* G,char* vexs,int* arcs){
    for(int i = 0;i<G->vexnum;i++){
        G->vexs[i] = vexs[i];
        for(int j = 0;j<G->vexnum;j++){
            G->arcs[i][j] = *(arcs+i*G->vexnum+j);   //二维数组中用列指针只能这样赋值  
            if(G->arcs[i][j]!=0){        // i*G->vexNum是移动i行    j是移动j列
                G->arcnum++;
            }                                        
        }
    }
    G->arcnum /=2;
}

void DFS(Graph* G,int index,int* visited){
    printf("%c ",G->vexs[index]);
    visited[index]=1;
    for(int i = 0;i<G->vexnum;i++){
        if(G->arcs[index][i] >0 && visited[i] == 0){
            DFS(G,i,visited);
        }
    }
}
int main(){
    Graph* G = initGraph(5);
    int* visited = (int*)malloc(sizeof(int)*G->vexnum);
    for(int i  =0;i<G->vexnum;i++){
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
    DFS(G,0,visited);
    // printf("\n");
    // for(int i  =0;i<G->vexNum;i++){
    //     visited[i] = 0;
    // }
    // BFS(G,visited,0);
    return 0;
}