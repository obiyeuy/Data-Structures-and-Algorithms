#include "stdio.h"
#include "MGraph.h"
#include <iostream>
int main(){
	MGraph G;
	CreateGraph( G );
	Output(G);
	printf("深度优先搜索的结果:\n");
    DFSTraverse(G,visit);
	printf("广度优先搜索的结果:\n");
    BFSTraverse(G,visit);
	if(G.kind==UDN){//计算无向网的最小生成树
		printf("普里姆算法计算最小生成树,请输入起始的顶点u:\n");
		VertexType u;
		scanf("%c",&u);
		printf("生成树的各边为：\n");
		MiniSpanTree_PRIM(G,u);
	}
	if(G.kind==DN){//迪杰斯特拉计算有向网的最短路径
		printf("迪杰斯特拉算法计算最短路径,请输入起始的顶点u:\n");
		VertexType u;
		scanf("%c",&u);
		PathMatrix P;
		ShortPathTable D;
		ShortestPath_DIJ( G,LocateVex(G,u),P,D);//调用迪杰斯特拉算法计算
		printf("计算结果如下：\n");
		printf("最短距离：\n");
		for(int k=0;k<G.vexnum;k++)
			printf("D[%c-%c]= %d ",u,G.vexs[k],D[k]);
		printf("\n路径：（若P[v][w]为TRUE，则w是从v0到v当前求得最短路径上的顶点。）\n");
		printf("  ");
		for( int i=0;i<G.vexnum;i++)
			printf("%c ",G.vexs[i]);
		printf("\n");
		for(int m=0; m<G.vexnum;m++){
			printf("%c ",G.vexs[m]);
			for(int n=0; n<G.vexnum;n++)
				printf("%d ",P[m][n]);
			printf("\n");
		}

		printf("采用FLOYD算法计算各个顶点间的最短路径\n");
		PathMatrix PF[MAX_VERTEX_NUM];
		DistancMatrix DF;
		ShortestPath_FLOYD( G,  PF, DF);
		printf("计算结果如下\n各个顶点间的最短距离为：\n  ");

		for(int t=0;t<G.vexnum;t++)
			printf("%c ",G.vexs[t]);
		printf("\n");
		for(int v=0;v<G.vexnum;v++){
			printf("%c ",G.vexs[v]);
			for(int w=0;w<G.vexnum;w++){
				if(DF[v][w] == INFINITY) 
					printf("^ ");//输出^表示无路可达
				else printf("%d ",DF[v][w]);
			}
		printf("\n");
		}

		printf("各个顶点的最短路径为：\n ");
		for(int x=0;x<G.vexnum;x++){
			printf("%c到其他顶点的最短路径为：\n  ",G.vexs[x]);
			for( int i=0;i<G.vexnum;i++)
				printf("%c ",G.vexs[i]);
			printf("\n");
			for(int y=0;y<G.vexnum;y++ ){
				printf("%c ",G.vexs[y]);
				for(int z=0;z<G.vexnum;z++)
					printf("%d ",PF[x][y][z]);//从x到y的最短路径	
				printf("\n");
			}
		}
	}
	return 0;
}