// ������͵�����
#include<iostream>
using namespace std;
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
void CreateList(LinkList &L,int n){
	//����һ��n��Ԫ�ص����Ա�ͷ�巨������¼���Ϊ��β�������¼���Ϊ��ͷ
	L=(LinkList) malloc (sizeof(LNode));
	L->next=NULL;
	for(LinkList p;n>=1;n--){
		p=(LinkList) malloc (sizeof(LNode));
		cout<<"�������"<<n<<"��Ԫ��";
		cin>>p->data;
		p->next=L->next;
		L->next=p;
	}
}
void TraverseList(LinkList L){//����
	LinkList p=L->next;
	while(p){
		cout<<p->data<<" ";
		p=p->next;
	}

}
void ReverseList(LinkList &L){//����
/*	LinkList p=L->next;
	LinkList q=p->next;
	p->next=NULL;
	while(q){
		L->next=q;
		q=q->next;
		L->next->next=p;
		p=L->next;
	}*/
	LinkList p=L->next;
	L->next=NULL;
	LinkList q;
	while(p){
		q=p->next;
		p->next=L->next;
		L->next=p;
		p=q;
	}
}
int main(){//������
	LinkList L;
	CreateList(L,5);//��������L,5��Ԫ��
	cout<<"����L=";
	TraverseList(L);//�����������L

	cout<<"\n"<<"L������=";
	ReverseList(L);//��������L
    TraverseList(L);//�����������L
	return 0;
}
