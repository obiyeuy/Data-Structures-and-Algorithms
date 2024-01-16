/*���ݽṹ��ҵ�� 
 ʵ�����Ա�a1,a2,...an���ĵ�����洢�ṹ��
 ��������ʵ�ֲ��ҵ�i��Ԫ�أ�
 �ڵ�i��λ�ò���һ��Ԫ�أ�
 ɾ����i��Ԫ�صĳ���

���ߣ�***
ʱ�䣺2020.3.3
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
      ElemType        data;   // ������
      struct LNode   *next;  // ָ����
   } LNode, *LinkList;  

LinkList InitList();//���������������ͷ��㣩 
LinkList CreateList();//����������Ϣ������������ĺ���(�д���һ�������� 
 

int GetElem();//���ҵ�i��Ԫ�صĺ��� 
int ListInsert();//������ĳλ�ò���ڵ�ĺ���
int ListDelete();//ɾ������ڵ�ĺ���    


int main(){
	LinkList L;
	L=InitList();   //����һ���յĴ�ͷ�ڵ�����Ա�L��
	L=CreateList();//��ʾ�û��������ݹ��������������д���һ�������� 
	
	
	
	int i;//���ҵ�iλͬѧ����Ϣ������� 
	printf("����Ҫ���ҵڼ�λͬѧ�����ݣ�\n");
	scanf("%d",&i);
	ElemType e1;
	GetElem(L,i,&e1); 
	printf("��%dλͬѧ����Ϣ���£�\n������%s\n���䣺%d\n�Ա�%s\n������%f\n",i,e1.name,e1.age,e1.sex,e1.score);
	
	int j;//���ҵ�iλͬѧ����Ϣ�������ɾ���������ͬѧ��Ϣ 

	printf("����Ҫɾ���ڼ�λͬѧ�����ݣ�\n");
	scanf("%d",&j);

	ElemType e2; 
	ListDelete(L,j,&e2);

	printf("���ĺ�����ͬѧ��Ϣ���£�\n");

	LinkList p;
	p=L->next;
	int k=1;
	while(p){
		printf("��%dλͬѧ����Ϣ���£�\n������%s\n���䣺%d\n�Ա�%s\n������%f\n",k,p->data.name,p->data.age,p->data.sex,p->data.score);
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
	printf("�������%dλͬѧ��������\n",i);
	scanf("%s",p->data.name);
	printf("�������%dλͬѧ�����䣺\n",i);
	scanf("%d",&p->data.age);
	printf("�������%dλͬѧ���Ա�\n",i);
	scanf("%s",p->data.sex);
	printf("�������%dλͬѧ�ķ�����\n",i);
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
	int j = 1;  // pָ���һ����㣬jΪ������
	
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


