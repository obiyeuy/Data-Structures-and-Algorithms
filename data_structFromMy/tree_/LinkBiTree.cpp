#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
#include<iostream>
#include<stack>
#include<queue>
using namespace std;

#define LIST_INIT_SIZE 100
#define LISTINCREMNET 20

typedef char TElemType;

typedef struct BiTNode {
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode,*BiTree;

bool CreateBiTree(BiTree &T) {
	char ch;
	scanf(&ch);
	if (ch == '#') {
		T == NULL;
	}else{
		T = (BiTNode*)malloc(sizeof(BiTNode));
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return true;
}

void visit(TElemType& e) {
	printf("%c",e);
}

//先序遍历递归描述
void Preorder(BiTree T, void(*visit)(TElemType& e)) {
	if (T) {
		visit(T->data);
		Preorder(T->lchild, visit);
		Preorder(T->rchild, visit);
	}
}

//中序遍历递归描述
void Inorder(BiTree T, void(*visit)(TElemType& e)) {
	if (T) {
		Inorder(T->lchild, visit);
		visit(T->data);
		Inorder(T->rchild, visit);
	}
}

//后序遍历递归描述
void Afterorder(BiTree T, void(*visit)(TElemType& e)) {
	if (T) {
		Afterorder(T->lchild, visit);
		Afterorder(T->rchild, visit);
		visit(T->data);
	}
}

//先序遍历的非递归算法
void PreOrder_I(BiTree T){
	BiTNode*q,*p = T;
	stack<BiTree> S;
	if(p!=NULL){
		S.push(p);
	}
	while(!S.empty()){
		q = S.top();
		S.pop();
		visit(q->data);
		if(q->rchild){
			S.push(q->rchild);
		}
		if(q->lchild){
			S.push(q->lchild);
		}
	}
}

//中序遍历算法的非递归描述
BiTNode* GoFarLeft(BiTree T,stack<BiTree> S) {
	if (!T) {
		return NULL;
	}
	while (T->lchild) {
		S.push(T);
		T = T->lchild;
	}
	return T;
}

void Inorder_I(BiTree T, void(*visit)(TElemType& e)) {
	stack<BiTree> S;
	BiTree t = GoFarLeft(T, S);   
	while (t) {
		visit(t->data);
		if (t->rchild) {
			t = GoFarLeft(t->rchild, S);
		}
		else if (!(S.empty())) {  //栈不空时退栈
			t = S.top();
			S.pop();
		}
		else {   //栈空表明遍历结束
			t = NULL;
		}
	}
}

//遍历算法的应用
// 1、统计二叉树中叶子结点的个数(先序遍历)
// 2、求二叉树的深度(后序遍历)
// 3、复制二叉树(后序遍历)
// 4、建立二叉树的存储结构
// 5、二叉树的层次遍历

// 统计二叉树中叶子结点的个数  
//算法基本思想：需在遍历算法中增添一个“计数”的参数，并将算法中“访问结点”的操作改为：若是叶子，则计数器增1
void CountLeaf(BiTree T,int& count){
	if(T){
		if((!T->lchild)&&(!T->rchild)){
			count++;  //对叶子节点计数
		}
		CountLeaf(T->lchild,count);
		CountLeaf(T->rchild,count);
	}
}

//求二叉树的深度(后序遍历)
//算法基本思想：二叉树的深度应为其左、右子树深度的最大值加1。
// 由此，需先分别求得左、右子树的深度，算法中“访问结点”的操作为：求得左、右子树深度的最大值，然后加 1 
int Depth(BiTree T){
	int depthLeft,depthRight;
	if(!T){
		return 0;
	}else{
		depthLeft = Depth(T->lchild);
		depthRight = Depth(T->rchild);
		return depthLeft>depthRight ? depthLeft : depthRight;
	}
}

//复制二叉树
//生成一个二叉树的结点
// (其数据域为item,左指针域为lptr,右指针域为rptr)
BiTNode *GetTreeNode(TElemType item,BiTNode *lptr,BiTNode *rptr){
	BiTree T;
	if(!(T = (BiTNode*)malloc(sizeof(BiTNode)))){
		return NULL;
	}
	T->data = item;
	T->lchild = lptr;
	T->rchild = rptr;
	return T;
}
BiTNode *CopyTree(BiTNode *T){
	BiTNode * temp;
	if(!T){
		return NULL;
	}
	if(T->lchild){
		temp->lchild = CopyTree(T->lchild);
	}else{
		temp->lchild = NULL;
	}
	if(T->rchild){
		temp->rchild = CopyTree(T->rchild);
	}else{
		temp->rchild = NULL;
	}
	BiTNode* newT = GetTreeNode(T->data,temp->lchild,temp->rchild);
	return newT;
}

//由先缀表达式建树算法
//基本操作：
// scanf(&ch);
// if ( In(ch, 字母集 )) 建叶子结点;
// else { 建根结点;
// 		  递归建左子树;
// 		  递归建右子树;
// }


// 由中缀表达式建树(含括号)？？？？
// 基本操作：
// scanf(&ch);
// if (In(ch, 字母集 )) { 建叶子结点; 暂存; }
// else if (In(ch, 运算符集)){ 
//    和前一个运算符比较优先数;
//    若当前的优先数“高”，则暂存;
//    否则建子树;
// }

// void CrtNode(BiTree& T,char ch){
// 	T = (BiTNode*)malloc(sizeof(BiTNode));
// 	T->data = ch;
// 	T->lchild = T->rchild = NULL;
	
// }
// void CrtExptree(BiTree &T,char exp[]){
// 	stack<char> S;
// 	S.push('#');
// 	stack<char>PTR;
// 	char* p = exp;
// 	char ch = *p;
// 	while(!(S.top() == '#'&& ch=='#')){
// 		if(!)
// 	}
// }


//由二叉树的先序和中序序列建树
// void CrtBT(BiTree& T,string pre,string ino){
// 	if(pre=="\0" || ino == "\0"){
// 		T = NULL;
// 	}else{
// 		int pos = ino.find(pre[0]);
// 		if(pos == -1){
// 			T =NULL;
// 		}else{
// 			T = (BiTNode*)malloc(sizeof(BiTNode));
// 			T->data = pre[0];
// 			T->lchild=T->rchild = NULL;
// 			CrtBT(T->lchild,pre.substr(1,pos),ino.substr(0,pos));
// 			CrtBT(T->rchild,pre.substr(pos+1),ino.substr(pos+1));
// 		}
// 	}
// }

//二叉树的层序遍历
void LevelOrderTraverse(BiTree T){
	queue<BiTree>Q;
	if(T){
		Q.push(T);
	}
	while(!Q.empty()){
		BiTree E = Q.front();
		visit(E->data);
		Q.pop();
		if(E->lchild){
			Q.push(E->lchild);
		}
		if(E->rchild){
			Q.push(E->rchild);
		}
	}
}


// int main(){
// 	string s1 = "ABELDHMIJ";
// 	string s2 = "ELBAMHIDJ";
// 	BiTree T;
// 	CrtBT(T,s1,s2);
// 	Afterorder(T,visit);
// }

int main() {
	BiTree a;
	CreateBiTree(a);
	a->data = 'a';
	BiTNode* c;
	CreateBiTree(c);
	c->data = 'c';
	a->lchild = c;
	BiTNode* b;
	CreateBiTree(b);
	b->data = 'b';
	a->rchild = b;
	Inorder_I(a, visit);
}