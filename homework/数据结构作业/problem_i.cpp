#include<iostream>
using namespace std;
#define NUM 100
#define BUSY 0
#define REST 1

typedef struct node
{
	char data;
	struct node* lchild;
	struct node* rchild;
	int lcount;
	int rcount;
}*TNode, Tnode;

/*关于线索化二叉树函数中Tree和p的关系：以p的视角来看p永远是Tree的前驱，Tree永远是p的后继，所以在p的右孩子为空或者Tree的左孩
子为空时，让p->rchild=Tree，Tree->lchild=p，用这样的方式以中序遍历的方式依次为每个节点寻找它的前驱和后继，以此完成二叉树的线
索化*/

void createhead(TNode& p)//初始化表头
{
	p = new Tnode;
	p->data = 'Z';
	p->lcount = p->rcount = -1;
	p->lchild = p->rchild = NULL;
}
void Createtree(TNode& Tree)//建立二叉树
{
	char ch;
	cin >> ch;
	if (ch == '#')Tree = NULL;
	else
	{
		Tree = new Tnode;
		Tree->data = ch;
		Tree->lcount = BUSY;
		Tree->rcount = BUSY;
		Createtree(Tree->lchild);
		Createtree(Tree->rchild);
	}
}
void Endnode(TNode& T, TNode& t)//求出二叉树中序遍历最后一个结点，并让最后一个结点的右孩子指向表头
{
	TNode p = T;
	while (p->rchild)p = p->rchild;
	p->rchild = t;
}


void Linktree(TNode Tree, TNode& p)//线索化二叉树
{

	if (Tree)
	{
		Linktree(Tree->lchild, p);
		if (p->rchild == NULL)//在产生后继后，用p代替刚才的"当前节点"，来给当前节点寻找后继(在p->rchild == NULL)
		{
			p->rcount = REST;
			p->rchild = Tree;
		}
		if (Tree->lchild == NULL)//因为无法预知后继，所以给当前节点寻找已知的前驱(在Tree->lchild == NULL的情况下)
		{
			Tree->lcount = REST;
			Tree->lchild = p;
			
		}
		
		p = Tree;
		Linktree(Tree->rchild, p);
	}

}

void printtree(TNode Head)//遍历线索二叉树(非递归)
{
	TNode p = Head->lchild;
	while (p != Head)
	{
		while (p->lcount == BUSY)//找到子树部分的最左结点，即子树部分中序遍历的第一个结点
		{
			p = p->lchild;
		}
		cout << p->data;
		while (p->rcount == REST && p->rchild != Head)
		{
			p = p->rchild;
			cout << p->data;//由于线索化过后，只要rcount==REST，就一直遍历右孩子，直到找到的结点有实际右孩子
		}
		p = p->rchild;  //进入子树的右子树
	}

}

void Count(TNode T,int& count){
	if(T){
		if(((!T->lchild)&&(T->rchild))||((!T->rchild)&&(T->lchild))){
			count++; 
		}
		Count(T->lchild,count);
		Count(T->rchild,count);
	}
}


int main()
{
	TNode Tree;             //创建二叉树根节点
	TNode p;                //创建线索化二叉树的跟踪节点
	TNode head = new Tnode;   //初始化头结点
	int count = 1;
	createhead(p);
	Createtree(Tree);
	Count(Tree,count);
	if(Tree != NULL){
		head->lchild = Tree;    
		Linktree(Tree, p);
		Endnode(Tree, head);
		printtree(head);
		printf("\n%d", count);
	}else{
		printf("\n0");
	}
	return 0;
}
