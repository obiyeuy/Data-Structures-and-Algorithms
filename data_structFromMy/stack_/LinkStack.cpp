#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int SElemtype;
typedef struct SNode {
	SElemtype data;
	struct SNode* next;
}SNode,*LinkStack;

bool InitStack_L(SNode*& S) {
	S = (SNode*)malloc(sizeof(SNode));
	if (!S) {
		return false;
	}
	S->next = NULL;
	return true;
}

bool PushStack_L(LinkStack& S, SElemtype e) {
	SNode* cur = (SNode*)malloc(sizeof(SNode));
	if (!cur) {
		return false;
	}
	cur->data = e;
	cur->next = S->next;
	S->next = cur;
	return true;
}


bool PopStack_L(LinkStack& S, SElemtype& e) {
	if (S->next == NULL) {
		return false;
	}
	SNode* tmp = S->next;
	e = tmp->data;
	S->next = tmp->next;
	free(tmp);
}
