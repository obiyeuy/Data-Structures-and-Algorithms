#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_TREE_SIZE 100

typedef char TElemType;


//双亲链表
typedef struct BPTNode {  //结点结构
	TElemType data;
	int *parent;  //双亲指针
	char LRTag;  //左右孩子标志域
}BPTNode;

typedef struct BPTree {  //树结构
	BPTNode nodes[MAX_TREE_SIZE];
	int num_node;    //结点数目
	int root;  //根节点的位置
}BPTree;