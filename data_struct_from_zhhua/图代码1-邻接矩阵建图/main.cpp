#include "stdio.h"
#include <iostream>
#include <climits>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int Boolean;
using namespace std;
//-----图的数组(邻接矩阵)存储表示-----
#define INFINITY INT_MAX //最大值 ∞
#define MAX_VERTEX_NUM 20//最大顶点个数
typedef char InfoType;
typedef int VRType;//顶点关系类型,即矩阵的元素类型
typedef char VertexType;//顶点类型
typedef enum{DG,DN,UDG,UDN}GraphKind;//{有向图，有向网，无向图，无向网}
typedef struct ArcCell { // 弧的定义
     VRType  adj;    // VRType是顶点关系类型。
             // 对无权图，用1或0表示相邻否；
             // 对带权图，则为权值类型。
     InfoType  *info;  // 该弧相关信息的指针
} ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct { // 图的定义
     VertexType vexs[MAX_VERTEX_NUM];   // 顶点信息
     AdjMatrix  arcs;      // 弧的信息
     int vexnum, arcnum;   // 顶点数，弧数
     GraphKind   kind;     // 图的种类标志
  } MGraph;
int LocateVex(MGraph G, VertexType u);//若图中存在顶点u，则返回其在图中的位置，否则返回-1
Status CreateGraph( MGraph &G );// 采用数组(邻接矩阵)表示法，构造图G的框架。
Status CreateUDN(MGraph &G);// 采用数组（邻接矩阵）表示法，构造无向网G。
Status CreateUDG(MGraph &G);//采用数组（邻接矩阵）表示法，构造无向图
Status CreateDN(MGraph &G);// 采用数组（邻接矩阵）表示法，构造有向网G。
Status CreateDG(MGraph &G);  // 采用数组（邻接矩阵）表示法，构造有向图G。
void Output(MGraph G);//输出图G

Status CreateGraph( MGraph &G ) {  // 算法7.1
    // 采用数组(邻接矩阵)表示法，构造图G。
	cout<<"请输入图的类型(0-有向图,1-有向网,2-无向图,3-无向网)"<<endl;//原算法补充
    //scanf(&G.kind);  // 自定义输入函数，读入一个随机值
	scanf("%d",&G.kind);//输入图的类型
	switch (G.kind) {
        case  DG: return CreateDG(G);   // 构造有向图G
        case  DN: return CreateDN(G);   // 构造有向网G
        case UDG: return CreateUDG(G);  // 构造无向图G
        case UDN: return CreateUDN(G);  // 构造无向网G，算法7.2
        default : return ERROR;
    }
} // CreateGraph

Status CreateDG(MGraph &G) {
  // 采用数组（邻接矩阵）表示法，构造有向图G。
  int i,j,k;
  VertexType  v1,v2;
  printf("G.vexnum :" );  scanf("%d",&G.vexnum);
  printf("G.arcnum :");   scanf("%d",&G.arcnum);
  getchar();  /* 加上此句getchar()!!! 吃回车 */
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  printf("请输入各顶点的信息(char):\n");
  for (i=0; i<G.vexnum; i++ ) {
    printf("G.vexs[%d] : ",i);
    scanf("%c",&G.vexs[i]);
    getchar();
  } // 构造顶点向量
  for (i=0; i<G.vexnum; ++i )  // 初始化邻接矩阵
    for (j=0; j<G.vexnum; ++j ) {
      G.arcs[i][j].adj = 0; //{adj,info}
      G.arcs[i][j].info= NULL;
    }
  printf("请输入每条边依附的顶点\n");
  for (k=0; k<G.arcnum; ++k ) {  // 构造邻接矩阵
	printf("input arc %d:\n",k+1);
    printf("arc from v1 (char) : ");  scanf("%c", &v1);getchar();
    printf("arc to v2 (char) : ");  scanf("%c", &v2);getchar();
   // printf("w (int) : " );   scanf("%d", &w); getchar();
                             // 输入一条边依附的顶点及权值
    i = LocateVex(G, v1);  j = LocateVex(G, v2);
          // 确定v1和v2在G中位置
    G.arcs[i][j].adj = 1;                // 弧<v1,v2>的权值
    // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息
  }
  return OK;
} // CreateDG
Status CreateDN(MGraph &G) {
  // 采用数组（邻接矩阵）表示法，构造有向网G。
  int i,j,k,w;
  VertexType  v1,v2;
  printf("G.vexnum :" );  scanf("%d",&G.vexnum);
  printf("G.arcnum :");   scanf("%d",&G.arcnum);
  getchar();  /* 加上此句getchar()!!! 吃回车 */
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  printf("请输入各顶点的信息(char):\n");
  for (i=0; i<G.vexnum; i++ ) {
    printf("G.vexs[%d] : ",i);
    scanf("%c",&G.vexs[i]);
    getchar();
  } // 构造顶点向量
  for (i=0; i<G.vexnum; ++i )  // 初始化邻接矩阵
    for (j=0; j<G.vexnum; ++j ) {
      G.arcs[i][j].adj = INFINITY; //{adj,info}
      G.arcs[i][j].info= NULL;
    }
  printf("请输入每条边依附的顶点及权值\n");
  for (k=0; k<G.arcnum; ++k ) {  // 构造邻接矩阵
	printf("input arc %d:\n",k+1);
    printf("arc from v1 (char) : ");  scanf("%c", &v1);getchar();
    printf("arc to v2 (char) : ");  scanf("%c", &v2);getchar();
    printf("w (int) : " );   scanf("%d", &w); getchar();
                             // 输入一条边依附的顶点及权值
    i = LocateVex(G, v1);  j = LocateVex(G, v2);
          // 确定v1和v2在G中位置
    G.arcs[i][j].adj = w;                // 弧<v1,v2>的权值
    // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息
  }
  return OK;
} // CreateDN

Status CreateUDG(MGraph &G) {//
  // 采用数组（邻接矩阵）表示法，构造无向图G。
  int i,j,k;
  VertexType  v1,v2;
  printf("G.vexnum :" );  scanf("%d",&G.vexnum);
  printf("G.arcnum :");   scanf("%d",&G.arcnum);
  getchar();  /*** 加上此句getchar()!!! 吃回车 ***/
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  printf("请输入各顶点的信息(char):\n");
  for (i=0; i<G.vexnum; i++ ) {
    printf("G.vexs[%d] : ",i);
    scanf("%c",&G.vexs[i]);
    getchar();
  } // 构造顶点向量
  for (i=0; i<G.vexnum; ++i )  // 初始化邻接矩阵
    for (j=0; j<G.vexnum; ++j ) {
      G.arcs[i][j].adj = 0; //{adj,info}
      G.arcs[i][j].info= NULL;
    }
  printf("请输入每条边依附的顶点\n");
  for (k=0; k<G.arcnum; ++k ) {  // 构造邻接矩阵
	printf("input arc %d:\n",k+1);
    printf("arc from v1 (char) : ");  scanf("%c", &v1);getchar();
    printf("arc to v2 (char) : ");  scanf("%c", &v2);getchar();
   // printf("w (int) : " );   scanf("%d", &w); getchar();
                             // 输入一条边依附的顶点及权值
    i = LocateVex(G, v1);  j = LocateVex(G, v2);
          // 确定v1和v2在G中位置
    G.arcs[i][j].adj = 1;                // 弧<v1,v2>的权值
    // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息
    G.arcs[j][i].adj = G.arcs[i][j].adj; // 置<v1,v2>的对称弧<v2,v1>
  }
  return OK;
} // CreateUDG
Status CreateUDN(MGraph &G) {//  算法 7.2
  // 采用数组（邻接矩阵）表示法，构造无向网G。
  int i,j,k,w;
  VertexType  v1,v2;
  printf("G.vexnum :" );  scanf("%d",&G.vexnum);
  printf("G.arcnum :");   scanf("%d",&G.arcnum);
  getchar();  /*** 加上此句getchar()!!! 吃回车 ***/
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  printf("请输入各顶点的信息(char):\n");
  for (i=0; i<G.vexnum; i++ ) {
    printf("G.vexs[%d] : ",i);
    scanf("%c",&G.vexs[i]);
    getchar();
  } // 构造顶点向量
  for (i=0; i<G.vexnum; ++i )  // 初始化邻接矩阵
    for (j=0; j<G.vexnum; ++j ) {
      G.arcs[i][j].adj = INFINITY; //{adj,info}
      G.arcs[i][j].info= NULL;
    }
  printf("请输入每条边依附的顶点及权值\n");
  for (k=0; k<G.arcnum; ++k ) {  // 构造邻接矩阵
	// 输入每条边依附的顶点及权值
	printf("input arc %d:\n",k+1);
    printf("arc from v1 (char) : ");  scanf("%c", &v1);getchar();
    printf("arc to v2 (char) : ");  scanf("%c", &v2);getchar();
    printf("weight (int) : " );   scanf("%d", &w); getchar();

    i = LocateVex(G, v1);  j = LocateVex(G, v2);
          // 确定v1和v2在G中位置
    G.arcs[i][j].adj = w;                // 弧<v1,v2>的权值
    // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息
    G.arcs[j][i].adj = G.arcs[i][j].adj; // 置<v1,v2>的对称弧<v2,v1>
  }
  return OK;
} // CreateUDN
int LocateVex(MGraph G, VertexType u){//若图中存在顶点u，则返回其在图中的位置，否则返回-1
	for(int i=0;i<G.vexnum;i++){
		if(u == G.vexs[i]) return i;
	}
	return -1;
}
void Output(MGraph G){//输出图G
	int i,j;
	switch (G.kind) {
        case  DG: cout<<"有向图G"<<endl;break;
        case  DN: cout<<" 有向网G"<<endl;break;
        case UDG: cout<<" 无向图G"<<endl;break;
        case UDN: cout<<" 无向网G"<<endl;break;
        default : cout<<"ERROR"<<endl;
    }
	cout<<"The MGraph G is:"<<endl;
	cout<<"   ";
	for( i=0;i<G.vexnum;i++)
		cout<<G.vexs[i]<<"  ";
	cout<<endl;
	for( i=0;i<G.vexnum;i++)
		cout<<"——";
	cout<<endl;
	for( i = 0;i<G.vexnum;i++){
		cout<<G.vexs[i]<<" |";
		for( j = 0;j<G.vexnum;j++){
			if(G.arcs[i][j].adj == INFINITY)   cout<<"∞ ";
			else  cout<<G.arcs[i][j].adj<<" ";
		}
		cout<<endl;
	}
}
int main(){
	MGraph G;
	CreateGraph( G );
	Output(G);
	return 0;
}
