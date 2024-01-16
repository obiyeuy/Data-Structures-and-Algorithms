//弗洛伊德算法(求每对顶点之间的最短路径)
// D二维数组:保存了两点的最短路径
// P二维数组:保存了两点之间最短路径的前驱

//核心：试探法，通过加入不同的点进行中转，选择出最优解

#include<stdio.h>
#include<stdlib.h>
#define MAX 32767

typedef struct Graph{
    char* vexs;  //顶点
    int** arcs;  //边(以邻接矩阵的方式存储)
    int vexNum;  //顶点数
    int arcNum;  //边数
}Graph;


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
            if(G->arcs[i][j]!=0 && G->arcs[i][j]!=MAX){        // i*G->vexNum是移动i行    j是移动j列
                G->arcNum++;
            }                                        
        }
    }
    G->arcNum /=2;
}

// DFS:深度优先遍历
void DFS(Graph* G,int* visited,int index){
    printf("%c ",G->vexs[index]);
    visited[index] = 1;
    for(int i =0;i<G->vexNum;i++){
        if(G->arcs[index][i] >0 && G->arcs[index][i] !=MAX && !visited[i]){
            DFS(G,visited,i);
        }
    }
}

void floyd(Graph* G){
    // D数组:保存了两点的最短路径
    // P数组:保存了两点之间最短路径的前驱
    int d[G->vexNum][G->vexNum];
    int p[G->vexNum][G->vexNum];
    for(int i = 0;i<G->vexNum;i++){
        for(int j = 0;j<G->vexNum;j++){
            d[i][j] = G->arcs[i][j];
            if(G->arcs[i][j]>0 && G->arcs[i][j] !=MAX){
                p[i][j] = i;
            }else{
                p[i][j] = -1;
            }
        }
    }
    //查看两个辅助数组
    // for(int i = 0;i<G->vexNum;i++){
    //     for(int j = 0;j<G->vexNum;j++){
    //         printf("%d\t",d[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // for(int i = 0;i<G->vexNum;i++){
    //     for(int j = 0;j<G->vexNum;j++){
    //         printf("%d\t",p[i][j]);
    //     }
    //     printf("\n");
    // }
    
    //算法核心
    for(int i = 0;i<G->vexNum;i++){
        for(int j = 0;j<G->vexNum;j++){
            for(int k = 0;k<G->vexNum;k++){
                if(d[j][i]+d[i][k] < d[j][k]){  //以i节点为中转能更小,则改变相应辅助数组值
                    d[j][k] = d[j][i]+d[i][k];
                    p[j][k] = p[i][k];  // !!!!!!注意此处前驱节点的更新
                }
            }
        }
    }
    //查看结果
    for(int i = 0;i<G->vexNum;i++){
        for(int j = 0;j<G->vexNum;j++){
            printf("%d\t",d[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0;i<G->vexNum;i++){
        for(int j = 0;j<G->vexNum;j++){
            printf("%d\t",p[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Graph* G = initGraph(4);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[4][4] = {
            0, 1, MAX, 3,
            1, 0, 2, 2,
            MAX, 2, 0, 8,
            3, 2, 8, 0
    };
    createGraph(G, "ABCD", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    floyd(G);
    return 0;
}