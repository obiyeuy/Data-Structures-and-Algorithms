// 最小生成树(Prim算法)
#include <stdlib.h>
#include <stdio.h>

#define MAX 32767
/**
 * 图顶点之间不通，那么邻接矩阵的值为MAX
 * 如果顶点是自己本身，那么值为0
 */
// MST性质：(V,E)是连通图，假设U是V的一个非空子集，(u,v)是一条最小权值的边。
//         如果u属于U，v属于U-V,那么必有(u,v)包含在最小生成树中

// Prim算法：找点法。从集合中根据边的大小找点
// 1.记录当前U集合的状态
// 2.选择最小边以及顶点加入到U集合中

typedef struct Graph
{
    char *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
} Graph;

Graph *initGraph(int vexNum)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->vexs = (char *)malloc(sizeof(char) * vexNum);
    G->arcs = (int **)malloc(sizeof(int *) * vexNum);
    for (int i = 0; i < vexNum; i++)
    {
        G->arcs[i] = (int *)malloc(sizeof(int) * vexNum);
    }
    G->vexNum = vexNum;
    G->arcNum = 0;
    return G;
}

void createGraph(Graph *G, char *vexs, int *arcs)
{
    for (int i = 0; i < G->vexNum; i++)
    {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexNum; j++)
        {
            G->arcs[i][j] = *(arcs + i * G->vexNum + j);
            if (G->arcs[i][j] != 0 && G->arcs[i][j] != MAX)
            {
                G->arcNum++;
            }
        }
    }
    G->arcNum /= 2;
}

void DFS(Graph *G, int *visited, int index)
{
    printf("%c ", G->vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vexNum; i++)
    {
        if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX && visited[i] == 0)
        { // 两点之间有边(不为0与MAX)且没被访问过
            DFS(G, visited, i);
        }
    }
}

void prim(Graph *G, int index)
{
    int *distance = (int *)malloc(sizeof(int) * G->vexNum);
    int *perVex = (int *)malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; i++)
    {
        distance[i] = G->arcs[index][i];
        perVex[i] = index;
    }
    for (int i = 0; i < G->vexNum - 1; i++)
    {
        int min = index;
        int minDistance = MAX;
        for (int j = 0; j < G->vexNum; j++)
        {
            if (distance[j] != 0 && minDistance > distance[j])
            {
                min = j;
                minDistance = distance[j];
            }
        }
        printf("v%c->v%c, weight=%d\n", G->vexs[perVex[min]], G->vexs[min], distance[min]);
        distance[min] = 0;
        for (int j = 0; j < G->vexNum; j++)
        {
            if (G->arcs[min][j] != 0 && G->arcs[min][j] != MAX && distance[j] > G->arcs[min][j])
            {
                distance[j] = G->arcs[min][j];
                perVex[j] = min;
            }
        }
        //     for(int i = 0;i<G->vexNum;i++){
        //     printf("%d\t%d\n",distance[i],perVex[i]);
        // }
    }
}


void kruskal(Graph* G){
    int* connected= (int*)malloc(sizeof(int)*G->vexNum);
    for(int i = 0;i<G->vexNum;i++){
        connected[i] = i;
    }
    int* edgeStart = (int*)malloc(sizeof(int)*G->arcNum);
    int* edgeEnd = (int*)malloc(sizeof(int)*G->arcNum);
    int* edgeWeight = (int*)malloc(sizeof(int)*G->arcNum);
    int num = 0;
    for(int i = 0;i<G->vexNum;i++){
        for(int j = i+1;j<G->vexNum;j++){    //无向图从i+1开始，只记录上三角矩阵
            if(G->arcs[i][j] != MAX && G->arcs[i][j] !=0){
                edgeStart[num] = i;
                edgeEnd[num] = j;
                edgeWeight[num] = G->arcs[i][j];
                num++;
            }
        }
    }

    for(int i =0;i< G->arcNum-1;i++){
        for(int j = 0;j<G->arcNum-1-i;j++){
            if(edgeWeight[j]>edgeWeight[j+1]){
                int tmp1 = edgeStart[j];
                edgeStart[j] = edgeStart[j+1];
                edgeStart[j+1] = tmp1;
                int tmp2 = edgeEnd[j];
                edgeEnd[j] = edgeEnd[j+1];
                edgeEnd[j+1] = tmp2;
                int tmp3 = edgeWeight[j];
                edgeWeight[j] = edgeWeight[j+1];
                edgeWeight[j+1] = tmp3;
            }
        }
    }

    for(int i = 0;i<G->arcNum;i++){
        int start = connected[edgeStart[i]];   //这个边的头节点所属的连通分量
        int end = connected[edgeEnd[i]];   //这个边的尾节点所属的连通分量
        if(start != end){  //不在一个连通分量就可以选择
            printf("v%c->v%c, weight=%d\n",G->vexs[edgeStart[i]],G->vexs[edgeEnd[i]],edgeWeight[i]);
            for(int j = 0;j<G->vexNum;j++){
                if(connected[j] == end){   //将两个连通分量标识更新为其中起点的连通分量
                    connected[j] = start;   
                }
            }
        }
    }
}


int main()
{
    Graph *G = initGraph(6);
    int *visited = (int *)malloc(sizeof(int) * G->vexNum);
    for (int i = 0; i < G->vexNum; i++)
    {
        visited[i] = 0;
    }
    int arcs[6][6] = {
        0, 6, 1, 5, MAX, MAX,
        6, 0, 5, MAX, 3, MAX,
        1, 5, 0, 5, 6, 4,
        5, MAX, 5, 0, MAX, 2,
        MAX, 3, 6, MAX, 0, 6,
        MAX, MAX, 4, 2, 6, 0};
    createGraph(G, "123456", (int *)arcs);
    DFS(G, visited, 0);
    printf("\n");
    prim(G, 0);
    printf("\n");
    kruskal(G);
    return 0;
}
