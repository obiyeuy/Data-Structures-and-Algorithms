#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int Elemtype;
typedef struct LNode{
	Elemtype data;
	struct LNode *next;
}LNode,*LinkList;

bool ListInit_L(LinkList &L) {
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL) {
		return false;
	}
	L->next = NULL;
	L->data = 0;
	return true;
}

bool IsEmpty_L(LinkList L) {
	return L->next == NULL;
}

void ClearList(LinkList& L) {
	LNode* cur = NULL;
	while (L->next) {
		cur = L;
		L = L->next;
		free(cur);
	}
}

bool GetElem_L(LinkList L, int i, Elemtype* e) {
	LNode* p = L->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i) {
		return false;
	}
	*e = p->data;
	return true;
}

bool ListInsert_L(LinkList L, int i, Elemtype e) {
	LNode* p = L;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!p || j > i - 1) {
		return false;
	}
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}


bool ListDelete_L(LinkList L, int i, Elemtype* e) {
	LNode* p = L;
	int j = 0;
	while (p->next && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1) {
		return false;
	}
	LNode* q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return true;
}

int main(){
    LinkList L;
    ListInit_L(L);
    ListInsert_L(L,1,2);
    int a = 0;
    GetElem_L(L,1,&a);
    printf("%d",a);
}