//克鲁斯卡尔算法
//找边法：(也是用了MST性质)
// 1.对边排序
// 2.选边(要在不形成环的前提下将边选入)

// 1.维护一个边的数组并排序
// 2.判断图是否形成环：需要一个辅助数组来记录当前索引的节点所属于哪个连通分量
// (刚开始连通分量标记就是各个顶点自己，加入一条边则将加入边的终点的连通分量标记改为起点的标记，并将此连通分量中标记全部更新) ???


#include<stdio.h>
#include<stdlib.h>
#define MAX 32767

typedef struct Graph{
    char* vexs;  //顶点
    int** arcs;  //边(以邻接矩阵的方式存储)
    int vexNum;  //顶点数
    int arcNum;  //边数
}Graph;

typedef struct Edge{
    int start;
    int end;
    int weight;
}Edge;

Edge* initEdge(Graph* G){
    int index = 0;
    Edge* edge = (Edge*)malloc(sizeof(Edge)*G->arcNum);
    for(int i = 0;i<G->vexNum;i++){
        for(int j = i+1;j<G->vexNum;j++){
            if(G->arcs[i][j] !=MAX){   //需要判断是否有边
                edge[index].start = i;   
                edge[index].end = j;
                edge[index].weight = G->arcs[i][j];
                index++; //边数组中位置向后移一位
            }
        }
    }
    return edge;
}

void sortEdge(Edge* edge,Graph* G){
    Edge tmp;
    for(int i = 0;i<G->arcNum-1;i++){
        for(int j = 0;j<G->arcNum-i;j++){
            if(edge[j].weight>edge[j+1].weight){
                tmp = edge[j];
                edge[j] = edge[j+1];
                edge[j+1] = tmp;
            }
        }
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
            if(G->arcs[i][j]!=0 && G->arcs[i][j]!=MAX){        // i*G->vexNum是移动i行    j是移动j列
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
        if(G->arcs[index][i] >0 && G->arcs[index][i]!=MAX && !visited[i]){
            DFS(G,visited,i);
        }
    }
}

void kruskal(Graph* G){
    int* connected = (int*)malloc(sizeof(int)*G->vexNum);
    for(int i =0;i<G->vexNum;i++){
        connected[i]  =i;
    }     // 2.判断图是否形成环：需要一个辅助数组来记录当前索引的节点所属于哪个连通分量
    Edge* edge = initEdge(G);
    sortEdge(edge,G);
    for(int i = 0;i<G->arcNum;i++){
        int start = connected[edge[i].start];
        int end = connected[edge[i].end];
        if(start !=end){
            printf("v%c --> v%c weight = %d\n",G->vexs[edge[i].start],G->vexs[edge[i].end],edge[i].weight);
            for(int j = 0;j<G->vexNum;j++){   //将connected辅助数组更新
                if(connected[j] == end){
                    connected[j] = start;
                }
            }
        }
    }
}

int main(){
    Graph* G = initGraph(6);
    int* visited = (int*)malloc(sizeof(int)*G->vexNum);
    for(int i  =0;i<G->vexNum;i++){
        visited[i] = 0;
    }
    int arcs[6][6] = {
        0, 6, 1, 5, MAX, MAX,
        6, 0, 5, MAX, 3, MAX,
        1, 5, 0, 5, 6, 4,
        5, MAX, 5, 0, MAX, 2,
        MAX, 3, 6, MAX, 0, 6,
        MAX, MAX, 4, 2, 6, 0
    };
    createGraph(G,"ABCDEF",(int*)arcs);
    DFS(G,visited,0);
    printf("\n");
    kruskal(G);
    return 0;
}
