// 迪杰斯特拉算法(寻找最短路径)
// 求目标顶点到其他顶点的最短路径
// S数组：记录了目标顶点到其他顶点的最短路径是否求得
// P数组：记录了目标顶点到其他顶点的最短路径的前驱节点
// D数组：记录了目标顶点到其他顶点的最短路径的长度

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

//找目标顶点到其他顶点中未找到最短路径的顶点中的最小值
int getMin(Graph* G,int* s,int* d){
    int min = MAX;
    int index;
    for(int i = 0;i<G->vexNum;i++){
        if(!s[i] & d[i]<min){
            min = d[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(Graph* G,int index){
    //准备辅助数组
    int* s = (int*)malloc(sizeof(int)*G->vexNum);
    int* p = (int*)malloc(sizeof(int)*G->vexNum);
    int* d = (int*)malloc(sizeof(int)*G->vexNum);
    //初始化辅助数组
    // S数组：记录了目标顶点到其他顶点的最短路径是否求得
    // P数组：记录了目标顶点到其他顶点的最短路径的前驱节点
    // D数组：记录了目标顶点到其他顶点的最短路径的长度
    // for(int i = 0;i<G->vexNum;i++){
    //     if(i==index){
    //         s[i] = 1;
    //     }else{
    //         s[i] = 0;
    //     }
    // }
    // for(int i = 0;i<G->vexNum;i++){
    //     if(G->arcs[index][i]>0 && G->arcs[index][i] !=MAX){
    //         p[i] = index;
    //     }else{
    //         p[i] = -1;
    //     }
    // }
    // for(int i = 0;i<G->vexNum;i++){
    //     if(G->arcs[index][i]>0 && G->arcs[index][i] !=MAX){
    //         d[i] = G->arcs[index][i];
    //     }else{
    //         d[i] = MAX;
    //     }
    //     if(i == index){
    //         d[i] = 0;
    //     }
    // }
    //合并初始化
    for(int i = 0;i<G->vexNum;i++){
        if(G->arcs[index][i]>0 && G->arcs[index][i] !=MAX){
            d[i] = G->arcs[index][i];
            p[i] = index;
        }else{
            d[i] = MAX;
            p[i] = -1;
        }
        if(i == index){   // G->arcs[index][i] == 0
            s[i] = 1;
            d[i] = 0;
        }else{
            s[i] = 0;
        }
    }
    // //查看辅助数组
    // for(int i = 0;i<G->vexNum;i++){
    //     printf("%d %d %d\n",s[i],p[i],d[i]);
    // }
    for(int i =0;i<G->vexNum-1;i++){
        int index = getMin(G,s,d);
        s[index] = 1;
        for(int j = 0;j<G->vexNum;j++){  //调整数组中最短路径的长度
            if(!s[j] && d[index]+G->arcs[index][j]<d[j]){  //没找到且有更短的路径则改变存储的值
                d[j] = d[index]+G->arcs[index][j];
                p[j] = index;
            }
        }
    }  
    //输出结果
    for(int i = 0;i<G->vexNum;i++){
        printf("%d %d %d\n",s[i],p[i],d[i]);
    }
}

int main() {
    Graph* G = initGraph(7);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[7][7] = {
            0, 12, MAX, MAX, MAX, 16, 14,
            12, 0, 10, MAX, MAX, 7, MAX,
            MAX, 10, 0, 3, 5, 6, MAX,
            MAX, MAX, 3, 0, 4, MAX, MAX,
            MAX, MAX, 5, 4, 0, 2, 8,
            16, 7, 6, MAX, 2, 0, 9,
            14, MAX, MAX, MAX, 8, 9, 0
    };
    createGraph(G, "ABCDEF", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    dijkstra(G, 0);
    return 0;
}