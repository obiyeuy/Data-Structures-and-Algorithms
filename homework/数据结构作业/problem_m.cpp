#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX 100

typedef struct Graph
{
    char *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
} Graph;

Graph *initGraph(int vexNum, int arcNum, int type)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->vexs = (char *)malloc(sizeof(char) * vexNum);
    G->arcs = (int **)malloc(sizeof(int *) * vexNum);
    for (int i = 0; i < vexNum; i++)
    {
        G->arcs[i] = (int *)malloc(sizeof(int) * vexNum);
        switch (type)
        {
        case 0:
        case 2:
            for (int j = 0; j < vexNum; j++)
            {
                G->arcs[i][j] = 0;
            }
            break;
        case 1:
        case 3:
            for (int j = 0; j < vexNum; j++)
            {
                if (i == j)
                {
                    G->arcs[i][i] = 0;
                }
                else
                {
                    G->arcs[i][j] = MAX;
                }
            }
            break;
        }
    }
    G->vexNum = vexNum;
    G->arcNum = arcNum;
    return G;
}

void createGraph(Graph *G, int type)
{
    for (int i = 0; i < G->vexNum; i++)
    {
        scanf("%s",&G->vexs[i]);
    }
    char left, right;
    int leftIndex, rightIndex;
    int weight;
    int count;
    switch (type)
    {
    case 0:
        for (int i = 0; i < G->arcNum; i++)
        {
            cin >> left >> right;
            for (int j = 0; j < G->vexNum; j++)
            {
                if (left == G->vexs[j])
                {
                    leftIndex = j;
                    count++;
                }
                if (right == G->vexs[j])
                {
                    rightIndex = j;
                    count++;
                }
                if(count == 2){
                    count = 0;
                    break;
                }
            }
            G->arcs[leftIndex][rightIndex] = 1;
        }
        break;
    case 1:
        for (int i = 0; i < G->arcNum; i++)
        {
            cin >> left >> right >> weight;
            for (int j = 0; j < G->vexNum; j++)
            {
                if (left == G->vexs[j])
                {
                    leftIndex = j;
                }
                if (right == G->vexs[j])
                {
                    rightIndex = j;
                }
            }
            G->arcs[leftIndex][rightIndex] = weight;
        }
        break;
    case 2:
        for (int i = 0; i < G->arcNum; i++)
        {
            cin >> left >> right;
            for (int j = 0; j < G->vexNum; j++)
            {
                if (left == G->vexs[j])
                {
                    leftIndex = j;
                }
                if (right == G->vexs[j])
                {
                    rightIndex = j;
                }
            }
            G->arcs[leftIndex][rightIndex] = 1;
            G->arcs[rightIndex][leftIndex] = 1;
        }
        break;
    case 3:
        for (int i = 0; i < G->arcNum; i++)
        {
            cin >> left >> right >> weight;
            for (int j = 0; j < G->vexNum; j++)
            {
                if (left == G->vexs[j])
                {
                    leftIndex = j;
                }
                if (right == G->vexs[j])
                {
                    rightIndex = j;
                }
            }
            G->arcs[leftIndex][rightIndex] = weight;
            G->arcs[rightIndex][leftIndex] = weight;
        }
        break;
    }
}

void DFS(Graph* G,int* visited,int index){
    printf("%c",G->vexs[index]);
    visited[index] = 1;
    for(int i = 0;i<G->vexNum;i++){
        if(G->arcs[index][i] >0 && G->arcs[index][i]!=MAX && !visited[i]){
            DFS(G,visited,i);
        }
    }
}

int main()
{
    int type, vexNum, arcNum;
    scanf("%d %d %d", &type, &vexNum, &arcNum);
    Graph *G = initGraph(vexNum, arcNum, type);
    createGraph(G, type);
    char vex;
    int index;
    cin>>vex;
    for(int i = 0;i<G->vexNum;i++){
        if(vex == G->vexs[i]){
            index = i;
            break;
        }
    }
    int* visited = (int*)malloc(sizeof(int)*G->vexNum);
    for(int i =0;i<G->vexNum;i++){
        visited[i] = 0;
    }
    DFS(G,visited,index);
    for(int i = 0;i<G->vexNum;i++){
        if(visited[i] == 0){
            DFS(G,visited,i);
        }
    }
    return 0;
}