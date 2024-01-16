#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMNET 20

typedef int SElemtype;

typedef struct {
	SElemtype *base;
	SElemtype *top;
	int stacksize;
}SqStack;


bool InitStack_Sq(SqStack &S) {
	S.base= (SElemtype*)malloc(LIST_INIT_SIZE * sizeof(SElemtype));
	if (!S.base) {
		return false;
	}
	S.top = S.base;
	S.stacksize = LIST_INIT_SIZE;
	return true;
}

bool IsFull(SqStack S) {
	if (S.top-S.base>=S.stacksize) {
		return true;
	}
	return false;
}

bool IsEmpty(SqStack S) {
	return S.top-S.base == 0;
}

void Inc(SqStack &S) {   //扩容
	S.base = (SElemtype*)realloc(S.base, (S.stacksize + LISTINCREMNET) * sizeof(SElemtype));
	S.stacksize += LISTINCREMNET;
	S.top = S.base + S.stacksize;
}

bool Push(SqStack& S, SElemtype e) {
	if (IsFull(S)) {
		Inc(S);
	}
	*S.top++ = e;
	return true;
}

bool Pop(SqStack& S, SElemtype& e) {
	if (S.top == S.base) {
		return false;
	}
	else {
		e = *(S.top - 1);
		S.top--;
	}
	return true;
}


// void Clear(SqStack& S) {
	
// }

