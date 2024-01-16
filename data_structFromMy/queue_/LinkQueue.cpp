#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int QElemtype;
typedef struct QNode {
	QElemtype data;
	struct QNode* next;
}QNode;

typedef struct {
	QNode* front;
	QNode* rear;
}LinkQueue;

bool InitQueue_L(LinkQueue& Q) {
	Q.front = Q.rear = (QNode*)malloc(sizeof(QNode));
	if (!Q.front) {
		return false;
	}
	Q.front->next = NULL;
	return true;
}

bool PushQueue_L(LinkQueue& Q, QElemtype e) {
	QNode* cur = (QNode*)malloc(sizeof(QNode));
	if (!cur) {
		return false;
	}
	cur->data = e;
	cur->next = NULL;
	Q.rear->next = cur;
	Q.rear = cur;
	return true;
}

bool PopQueue_L(LinkQueue& Q, QElemtype& e) {
	if (Q.front == Q.rear) {
		return false;
	}
	QNode* tmp = Q.front->next;
	e = tmp->data;
	Q.front->next = tmp->next;
	if (Q.rear == tmp) {
		Q.rear = Q.front;
	}
	free(tmp);
	return true;
}


// int main(){
//     LinkQueue Q;
//     InitQueue_L(Q);
//     PushQueue_L(Q,3);
//     int a = 0;
//     PopQueue_L(Q,a);
//     printf("%d",a);
// }