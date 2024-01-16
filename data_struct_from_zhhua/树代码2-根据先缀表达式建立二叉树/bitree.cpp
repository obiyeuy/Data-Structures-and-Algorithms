#include "stdio.h"
#include <iostream>
using namespace std;
#include "bitree.h"
Status CreateBiTree(BiTree &T) {
	TElemType ch;
    //scanf(&ch);//输入ch
	cin>>ch;
	if ((ch<='z'&&ch>='a')||(ch<='Z'&&ch>='A')) {
      if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
        exit(OVERFLOW);
      T->data = ch;              // 生成根结点
      T->lchild = NULL;   // 构造左子树
      T->rchild = NULL;   // 构造右子树	
	}
    else {
      if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
        exit(OVERFLOW);
      T->data = ch;              // 生成根结点
      CreateBiTree(T->lchild);   // 构造左子树
      CreateBiTree(T->rchild);   // 构造右子树
    }
    return OK;  
} // CreateBiTree 以字符串的形式输入表达式  -×+ a b c / d e

void PreOrder (BiTree T,void( *visit)(TElemType& e))
{ // 先序遍历二叉树 
   if (T) {
      visit(T->data);            // 访问结点
      PreOrder(T->lchild, visit); // 遍历左子树
      PreOrder(T->rchild, visit);// 遍历右子树
   }
}
void InOrder (BiTree T,void( *visit)(TElemType& e))
{ // 中序遍历二叉树 
   if (T) {
      InOrder(T->lchild, visit); // 遍历左子树
      visit(T->data);            // 访问结点
      InOrder(T->rchild, visit);// 遍历右子树
   }
}
void PostOrder (BiTree T,void( *visit)(TElemType& e))
{ // 后序遍历二叉树 
   if (T) {
      PostOrder(T->lchild, visit); // 遍历左子树 
      PostOrder(T->rchild, visit);// 遍历右子树      
	  visit(T->data);  // 访问结点
   }
}
void visit(TElemType& e){//访问函数
	cout<<e;
}



