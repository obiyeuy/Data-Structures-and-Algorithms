/*数据结构作业： 
 实现线性表（a1,a2,...an）的单链表存储结构，
 并在其上实现查找第i个元素，
 在第i个位置插入一个元素，
 删除第i个元素的程序。

作者：***
时间：2020.3.3
 */
 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Num_of_sudent 3

typedef  struct  data {
    char  name[10];
    int    age;
    char  sex[4];
    float  score;
}ElemType;                       


typedef struct  LNode {
      ElemType        data;   // 数据域
      struct LNode   *next;  // 指针域
   } LNode, *LinkList;  

LinkList InitList();//构造空链表函数（带头结点） 
LinkList CreateList();//输入链表信息创建具体链表的函数(有待进一步开发） 
 

int GetElem();//查找第i个元素的函数 
int ListInsert();//给链表某位置插入节点的函数
int ListDelete();//删除链表节点的函数    


int main(){
	LinkList L;
	L=InitList();   //构造一个空的带头节点的线性表L。
	L=CreateList();//提示用户输入数据构造具体的链表。（有待进一步开发） 
	
	
	
	int i;//查找第i位同学的信息并且输出 
	printf("您想要查找第几位同学的数据？\n");
	scanf("%d",&i);
	ElemType e1;
	GetElem(L,i,&e1); 
	printf("第%d位同学的信息如下：\n姓名：%s\n年龄：%d\n性别：%s\n分数：%f\n",i,e1.name,e1.age,e1.sex,e1.score);
	
	int j;//查找第i位同学的信息并且输出删除后的所有同学信息 

	printf("您想要删除第几位同学的数据？\n");
	scanf("%d",&j);

	ElemType e2; 
	ListDelete(L,j,&e2);

	printf("更改后所有同学信息如下：\n");

	LinkList p;
	p=L->next;
	int k=1;
	while(p){
		printf("第%d位同学的信息如下：\n姓名：%s\n年龄：%d\n性别：%s\n分数：%f\n",k,p->data.name,p->data.age,p->data.sex,p->data.score);
		p=p->next;
		k++;
	}
	
}

LinkList InitList(){
	LinkList L;
	L=(LNode *) malloc (sizeof (LNode));
	L->next=NULL;
        return L;
}

LinkList CreateList(){
	int i;
	LinkList L,r,p;
	
        L=(LNode *) malloc (sizeof (LNode));
	L->next=NULL;
	r=L;

	for(i=1;i<=Num_of_sudent;i++){
	p=(LNode *) malloc (sizeof (LNode));
	printf("请给出第%d位同学的姓名：\n",i);
	scanf("%s",p->data.name);
	printf("请给出第%d位同学的年龄：\n",i);
	scanf("%d",&p->data.age);
	printf("请给出第%d位同学的性别：\n",i);
	scanf("%s",p->data.sex);
	printf("请给出第%d位同学的分数：\n",i);
	scanf("%f",&p->data.score);	
	r->next=p;
	r=p;
	}
	r->next=NULL;
        return L;
	
} 

int GetElem(LinkList L, int i, ElemType *e){
	LinkList p;
	p = L->next;   
	int j = 1;  // p指向第一个结点，j为计数器
	
	while(p&&j<i){
		p=p->next;
		j++;
	};
	if(!p){
		return 0;
	}
	*e=p->data;
	return 1;

}




LinkList ListInsert(LinkList L,int i,ElemType e){
	LinkList p=L;
	int j=0;
	while(p&&j<i-1){
		p=p->next;
		++j;
	}
	if(!p){
		return 0;
	}
	LinkList s;
	s = (LinkList) malloc ( sizeof (LNode)); 
	s->data = e; 
	s->next = p->next;
	p->next = s; 
    return L;
	
} 


LinkList ListDelete(LinkList L, int i, ElemType *e){
	LinkList p=L;
	int j=0;
	while(p&&j<i-1){
		p=p->next;
		++j;
	}
	if(!(p->next)){
		return 0;
	}
	
	LinkList q;
	q=p->next;
	p->next=q->next;
	e=&(q->data);
	free(q);
	return L;
	
}


