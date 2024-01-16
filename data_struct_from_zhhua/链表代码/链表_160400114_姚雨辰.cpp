//链表。。头结点和头指针还是很有必要的
//代码主要按照自己的思路，功能和结构参照ppt
//欢迎bug反馈
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//宏定义两个值
#define YES 1
#define NO  0

typedef int element;

typedef struct Node{
	element data;
	Node *next;
}Node,*Link;


Link Get_element(Link hp, int k)//查找第几个结点
{
	Link p=hp;
	int times = 0;
	if (k < 1)
		return NULL;
	while (p&&times < k)
	{
		p = p->next;
		times++;
	}
	/*
	作业:
	作业是下面的那个式子，原式子为:
	if ( !p || j>i )
		return ERROR;
	!p很好理解，如果p是空指针，说明上面的循环提前跳出，或者刚好在第k个元素跳出(即使这样，第k个元素也是不存在)，不存在第k个元素，自然ERROR
	j>i感觉纯粹是为了判断k值是否合法，与其这样，倒不如最开始就判断一下，以免这种情况的时候还会遍历一下链表
	上面那个while改成while true也一样可以，只不过判断在里面，p为空指针直接returnERROR，j(times)=k的时候return成功就好

	还有对于本函数，我觉得写成现在这个样子,return找到元素的指针更好
	ppt上return OK有啥用，这函数的目的不就是找第几个元素嘛，又不是判断第几个元素存不存在（这么无聊的事情）
	所以找到之后直接返回就好，试试证明这东西对后面几个函数也很有用

	*/
	if (!p)
		return NULL;
	else
		return p;
}
int append_element(element e, Link hp)//向链表末尾添加一个元素
{
	Link p = hp;
	while (p->next != NULL)
	{
		p = p->next;
	}
	Link temp = (Link)malloc(sizeof(Node));
	temp->data = e;
	temp->next = NULL;
	p->next = temp;
	return YES;
}


int Insert_element(element e, int loc, Link hp)//将一个元素插入链表使之成为第loc个元素
{
	Link p;
	if (loc == 1)
		p = hp;
	else
		p=Get_element(hp, loc-1);
	if (p == NULL)
		return NO;
	Link newe = (Link)malloc(sizeof(Node));
	newe->data = e;
	newe->next = p->next;
	p->next = newe;
	return YES;
}

int delete_node(int loc, Link hp)//删除第loc个结点
{
	Link p;
	if (loc == 1)
		p = hp;
	else
		p = Get_element(hp, loc - 1);
	if (p == NULL||p->next==NULL)
		return NO;
	Link temp = p->next;
	p->next = p->next->next;
	free(temp);
	return YES;
}

int clear_list(Link hp)//清空链表
{
	Link temp=hp->next;
	Link temp2;
	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	hp->next = NULL;
	return YES;
}

void show_list(Link hp)//输出链表所有元素
{

	Link temp = hp->next;
	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
int main()
{
	//示例
	Node head;
	head.next = NULL;
	Link hp = &head;

	append_element(5, hp);
	append_element(4, hp);
	append_element(1, hp);
	append_element(2, hp);
	append_element(3, hp);
	show_list(hp);
	
	Insert_element(6, 2, hp);
	show_list(hp);
	Insert_element(8, 4, hp);
	show_list(hp);

	delete_node(3, hp);
	show_list(hp);
	delete_node(5, hp);
	show_list(hp);

	clear_list(hp);
	show_list(hp);

	system("pause");
}



