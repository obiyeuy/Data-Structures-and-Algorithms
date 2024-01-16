#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include <limits.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
//图的邻接表存储结构
#define INFINITY INT_MAX //最大值 ∞
#define MAX_VERTEX_NUM 20//最大顶点个数
typedef int VRType;//顶点关系类型
typedef char  InfoType;
typedef char VertexType;//顶点类型
typedef enum{DG,DN,UDG,UDN}GraphKind;//{有向图，有向网，无向图，无向网}
typedef struct ArcNode {  //弧的结点结构
  int        adjvex;   // 该弧所指向的顶点的位置
  struct ArcNode  *nextarc; // 指向下一条弧的指针
  VRType adj;  // 弧<v1,v2>的权值 这一条是照比教材后加的
  InfoType   *info;   // 该弧相关信息的指针
} ArcNode;
typedef struct VNode { //顶点的结点结构
  VertexType  data;   // 顶点信息
  ArcNode  *firstarc; // 指向第一条依附该顶点的弧

  } VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {  //图的结构定义
     AdjList  vertices;
     int      vexnum, arcnum;
     int      kind;          // 图的种类标志
  } ALGraph;
int LocateVex(ALGraph G, VertexType u){//若图中存在顶点u，则返回其在图中的位置，否则返回-1
	for(int i=0;i<G.vexnum;i++){
		if(u == G.vertices[i].data) return i;
	}
	return -1;
}
Status CreateDG(ALGraph &G) {//
  // 采用邻接表表示法，构造有向图G。
  int i,j,k;
  VertexType  v1,v2;
  printf("G.vexnum :" );  scanf("%d",&G.vexnum);
  printf("G.arcnum :");   scanf("%d",&G.arcnum);
  getchar();  /*** 加上此句getchar()!!! 吃回车 ***/
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  for (i=0; i<G.vexnum; i++ ) { //录入各个顶点，并初始化顶点的第一条弧或边是指针为空
    printf("G.vertices[%d].data : ",i);
    scanf("%c",&G.vertices[i].data);
    getchar();
	G.vertices[i].firstarc=NULL;
  } // 初始化图

  for (k=0; k<G.arcnum; ++k ) {  // 构造邻接表
	  // 输入一条边依附的顶点及权值
    printf("v1 (char) : ");  scanf("%c", &v1);getchar();
    printf("v2 (char) : ");  scanf("%c", &v2);getchar();


    i = LocateVex(G, v1);  j = LocateVex(G, v2); // 确定v1和v2在G中位置
     //建立<i,j>
    ArcNode* s= (ArcNode*)malloc(sizeof(ArcNode));
	s->adjvex = j;
	s->nextarc =G.vertices[i].firstarc;
	G.vertices[i].firstarc = s;
    // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息
  }
  return OK;
} // CreateDG


Status CreateDN(ALGraph &G) {//
  // 采用邻接表表示法，构造有向网G。
  int i,j,k,w;
  VertexType  v1,v2;
  printf("G.vexnum :" );  scanf("%d",&G.vexnum);
  printf("G.arcnum :");   scanf("%d",&G.arcnum);
  getchar();  /*** 加上此句getchar()!!! 吃回车 ***/
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  for (i=0; i<G.vexnum; i++ ) { //录入各个顶点，并初始化顶点的第一条弧或边是指针为空
    printf("G.vertices[%d].data : ",i);
    scanf("%c",&G.vertices[i].data);
    getchar();
	G.vertices[i].firstarc=NULL;
  } // 初始化图

  for (k=0; k<G.arcnum; ++k ) {  // 构造邻接表
	  // 输入一条边依附的顶点及权值
    printf("v1 (char) : ");  scanf("%c", &v1);getchar();
    printf("v2 (char) : ");  scanf("%c", &v2);getchar();
    printf("w (int) : " );   scanf("%d", &w); getchar();

    i = LocateVex(G, v1);  j = LocateVex(G, v2); // 确定v1和v2在G中位置
     //建立<i,j,w>
    ArcNode* s= (ArcNode*)malloc(sizeof(ArcNode));
	s->adjvex = j;
	s->adj = w;
	s->nextarc =G.vertices[i].firstarc;
	G.vertices[i].firstarc = s;
    // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息

  }
  return OK;
} // CreateDN
Status CreateUDG(ALGraph &G) {//
  // 采用邻接表表示法，构造无向图G。
  int i,j,k;
  VertexType  v1,v2;
  printf("G.vexnum :" );  scanf("%d",&G.vexnum);
  printf("G.arcnum :");   scanf("%d",&G.arcnum);
  getchar();  /*** 加上此句getchar()!!! 吃回车 ***/
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  for (i=0; i<G.vexnum; i++ ) { //录入各个顶点，并初始化顶点的第一条弧或边是指针为空
    printf("G.vertices[%d].data : ",i);
    scanf("%c",&G.vertices[i].data);
    getchar();
	G.vertices[i].firstarc=NULL;
  } // 初始化图

  for (k=0; k<G.arcnum; ++k ) {  // 构造邻接表
	  // 输入一条边依附的顶点及权值
    printf("v1 (char) : ");  scanf("%c", &v1);getchar();
    printf("v2 (char) : ");  scanf("%c", &v2);getchar();


    i = LocateVex(G, v1);  j = LocateVex(G, v2); // 确定v1和v2在G中位置
     //建立<i,j>
    ArcNode* s= (ArcNode*)malloc(sizeof(ArcNode));
	s->adjvex = j;
	s->nextarc =G.vertices[i].firstarc;
	G.vertices[i].firstarc = s;

	 //建立<j,i>
    ArcNode* t= (ArcNode*)malloc(sizeof(ArcNode));
	t->adjvex = i;
	t->nextarc =G.vertices[j].firstarc;
	G.vertices[j].firstarc = t;
    // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息
  }
  return OK;
} // CreateUDG
Status CreateUDN(ALGraph &G) {//
  // 采用邻接表表示法，构造无向网G。
  int i,j,k,w;
  VertexType  v1,v2;
  printf("G.vexnum :" );  scanf("%d",&G.vexnum);
  printf("G.arcnum :");   scanf("%d",&G.arcnum);
  getchar();  /*** 加上此句getchar()!!! 吃回车 ***/
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);
  for (i=0; i<G.vexnum; i++ ) { //录入各个顶点，并初始化顶点的第一条弧或边是指针为空
    printf("G.vertices[%d].data : ",i);
    scanf("%c",&G.vertices[i].data);
    getchar();
	G.vertices[i].firstarc=NULL;
  } // 初始化图

  for (k=0; k<G.arcnum; ++k ) {  // 构造邻接表
	  // 输入一条边依附的顶点及权值
    printf("v1 (char) : ");  scanf("%c", &v1);getchar();
    printf("v2 (char) : ");  scanf("%c", &v2);getchar();
    printf("w (int) : " );   scanf("%d", &w); getchar();

    i = LocateVex(G, v1);  j = LocateVex(G, v2); // 确定v1和v2在G中位置
     //建立<i,j,w>
    ArcNode* s= (ArcNode*)malloc(sizeof(ArcNode));
	s->adjvex = j;
	s->adj = w;
	s->nextarc =G.vertices[i].firstarc;
	G.vertices[i].firstarc = s;

	 //建立<j,i,w>
    ArcNode* t= (ArcNode*)malloc(sizeof(ArcNode));
	t->adjvex = i;
	t->adj = w;
	t->nextarc =G.vertices[j].firstarc;
	G.vertices[j].firstarc = t;

    // if (IncInfo) scanf(G.arcs[i][j].info); // 输入弧含有相关信息

  }
  return OK;
} // CreateUDN
Status CreateGraph( ALGraph &G ) {  // 算法7.1
    // 采用数组(邻接矩阵)表示法，构造图G。
	cout<<"请输入图的类型(0-有向图，1-有向网，2-无向图，3-无向网)"<<endl;//元算法补充
    //scanf(&G.kind);  // 自定义输入函数，读入一个随机值
	scanf("%d",&G.kind);//输入图的类型
	switch (G.kind) {
        case  DG: return CreateDG(G);   //构造有向图G
        case  DN: return CreateDN(G);   // 构造有向网G
        case UDG: return CreateUDG(G);  // 构造无向图G
        case UDN: return CreateUDN(G);  // 构造无向网G
        default : return ERROR;
    }
} // CreateGraph
Status CreateInverseGraph(ALGraph &IG,ALGraph G){//构造G的逆邻接表InverseG简写为IG
	int i,j;
	IG.kind=G.kind;IG.vexnum=G.vexnum;IG.arcnum=G.arcnum;
	for(i=0;i<G.vexnum;i++){//初始化IG
		IG.vertices[i].data=G.vertices[i].data;
		IG.vertices[i].firstarc=NULL;
	}
	for(i=0;i<G.vexnum;i++){//根据G求IG
		ArcNode *p = G.vertices[i].firstarc;
		while(p){
			ArcNode *s=(ArcNode *)malloc(sizeof(ArcNode));
			s->adj = p->adj;
			s->adjvex =i;
			s->info=p->info;
			s->nextarc = IG.vertices[p->adjvex].firstarc;
			IG.vertices[p->adjvex].firstarc = s;
			p=p->nextarc;
		}
	}
	return OK;
}


void Output(ALGraph G){//输出图G
	int i;
	switch (G.kind) {
        case  DG: cout<<"有向图"<<endl;break;
        case  DN: cout<<" 有向网"<<endl;break;
        case UDG: cout<<" 无向图"<<endl;break;
        case UDN: cout<<" 无向网"<<endl;break;
        default : cout<<"ERROR"<<endl;
    }
	for( i=0;i<G.vexnum;i++){
		cout<<i <<"|"<<G.vertices[i].data<<"|->";
		ArcNode *p = G.vertices[i].firstarc;
		while(p){
			if(G.kind==DN||G.kind==UDN)//有向网，无向网要输出权重p->adj
				cout<<"|"<<p->adjvex<<","<<G.vertices[p->adjvex].data<<","<<p->adj<<"|->";
			else//有向图，无向图不需要输出p->adj
				cout<<"|"<<p->adjvex<<","<<G.vertices[p->adjvex].data<<"|->";
			p=p->nextarc;
		}
		cout<<"NULL"<<endl;
	}
}

int main(){
	ALGraph G;
	ALGraph InverseG;
	CreateGraph(G);//邻接表方式建图或网
	if(G.kind==DG||G.kind==DN)//建立G的逆邻接表InverseG
		CreateInverseGraph(InverseG,G);
	cout<<"邻接表为G\n";
	Output(G);
	if(G.kind==DG||G.kind==DN){//输出逆邻接表
		cout<<"逆邻接表为InverseG\n";
		Output(InverseG);
	}
	return 0;
}
