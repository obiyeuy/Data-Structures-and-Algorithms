#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stack>
#include<queue>

#define INFINITY INT_MAX //最大值，表示无穷大
#define MAX_VERTEX_NUM 100 //最大顶点个数

typedef int VRType;
typedef char InfoType;
typedef int VertexType;

typedef enum {DG, DN, UDG, UDN} GraphKind;
typedef struct ArcCell { // 弧的定义
    VRType adj; // VRType是顶点关系类型
        // 对无权图，用1或0表示是否相邻
        // 对带权图，则为权值类型
    InfoType *info; // 该弧相关信息的指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


typedef struct { // 图的类型定义
    VertexType vexs[MAX_VERTEX_NUM]; // 顶点信息
    AdjMatrix arcs; // 弧的信息
    int vexnum, arcnum; // 顶点数，弧数
    GraphKind kind; // 图的种类标志
} MGraph;

void Creatgraph(MGraph &G){
    int i, j, k; float w;
    scanf("%d,%d,%d",G.vexnum, G.arcnum, G.kind);
    for(i=1;i<=G.vexnum;i++)
        G.vexs[i]=getchar();
    for(i=1;i<=G.vexnum;i++)
        for(j=1;j<=G.vexnum;j++){
            G.arcs[i][j].adj=INFINITY;
            G.arcs[i][j].info=NULL;
        }
        for (k=1;k<=G.arcnum;k++) {
            scanf("%d,%d,%f",&i,&j,&w);
            G.arcs[i][j].adj=w; G.arcs[j][i].adj=w;
    }
}
