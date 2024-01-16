#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;

#define MAX 100

typedef struct ArcNode{
    int adjvex;   //改变所指顶点的位置
    struct ArcNode* nextarc;  //指向下一条边的指针
    // OtherInfo info;   //边相关的其他信息
}ArcNode;

typedef struct VNode{
    // VerTexType data;    //顶点信息
    char data;
    ArcNode* firstarc;
}VNode,AdjList[MAX];

typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;


int locateVex(ALGraph G,char v){
    for(int i = 0;i<G.vexnum;i++){
        if(G.vertices[i].data == v){
            return i;
        }
    }
    return -1;
}

void createUDG(ALGraph &G){
    cin>>G.vexnum>>G.arcnum;
    for(int i = 0;i<G.vexnum;i++){   //输入各点，构造表头结点表
        cin>>G.vertices[i].data;
        G.vertices[i].firstarc = NULL;   //初始化表头结点的指针域
    }
    char v1,v2;
    for(int k = 0;k<G.arcnum;k++){
        cin>>v1>>v2;
        int i = locateVex(G,v1);
        int j = locateVex(G,v2);
        ArcNode* p1 = new ArcNode;
        p1->adjvex = j;
        p1->nextarc = G.vertices[i].firstarc;  //将头节点后面的赋给p1的next域
        G.vertices[i].firstarc = p1;  //然后将p1接在头节点后面     也即头插法
        ArcNode* p2 = new ArcNode;
        p2->adjvex = i;
        p2->nextarc = G.vertices[j].firstarc;  //将头节点后面的赋给p1的next域
        G.vertices[j].firstarc = p2;
    }
}

int main(){
    ALGraph* G = new ALGraph;
    createUDG(*G);
    for(int i = 0;i<G->vexnum;i++){
        printf("%c ",G->vertices[i].data);
    }
    return 0;
}