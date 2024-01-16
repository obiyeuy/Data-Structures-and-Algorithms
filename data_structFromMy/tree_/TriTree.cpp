#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef char TElemType;


//三叉链表
typedef struct TriTNode {
	TElemType data;
	struct TriTNode* lchild, * rchild;
	struct TriNode* parent;  //双亲指针
}TriTNode, * TriTree;