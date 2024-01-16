#include "stack_op.h"
#include "stack.h"
#include <iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

/*typedef char TElemType;
typedef struct BiTNode { // 结点结构
    TElemType      data;
    struct BiTNode  *lchild, *rchild; // 左右孩子指针                                  
} BiTNode, *BiTree; */ //结点及树的定义在stack.h中
void CrtExptree(BiTree &T, char exp[] );//以表达式字符串的形式建立一颗表达式二叉树,(a+b)*c-d/e
void PreOrder (BiTree T,void( *visit)(TElemType& e));//先根遍历
void InOrder (BiTree T,void( *visit)(TElemType& e));//中根遍历
void PostOrder (BiTree T,void( *visit)(TElemType& e));//后根遍历
void visit(TElemType& e);//访问函数
void CrtNode(BiTree& T,char ch);//建立叶子节点
void CrtSubtree (BiTree& T, char c);//建立子树
Status IN(char ch,char OP[]);//看ch是否属于OP，如果是返回TRUE，否则返回ERROR
Status precede(char c,char ch);//比较运算符c和ch的优先级,c高于ch返回true，否则返回FALSE
