#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_TREE_SIZE 100;

typedef char TElemType;


//孩子结点结构
typedef struct CTNode{
    int child;
    struct CTNode *next;
}*ChildPtr;

typedef struct{
    TElemType data;
    ChildPtr firstChild;// 孩子链的头指针
}CTBox;

typedef struct{
    // CTBox nodes[MAX_TREE_SIZE];
    int num_node;
    int root; // 结点数和根结点的位置
}CTree;