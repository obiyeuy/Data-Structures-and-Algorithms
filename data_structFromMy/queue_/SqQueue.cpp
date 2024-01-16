#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXQSIZE 100
#define LISTINCREMNET 20

typedef int QElemtype;

typedef struct {
	QElemtype* base;
	int front;
	int rear;
}SqQueue;


bool InitQueue_Sq(SqQueue& Q) {
	Q.base = (QElemtype*)malloc(MAXQSIZE * sizeof(QElemtype));
	if (!Q.base) {
		return false;
	}
	Q.front = Q.rear = 0;
	return true;
}

bool PushQueue_Sq(SqQueue& Q, QElemtype e) {
	if ((Q.rear + 1) % MAXQSIZE == Q.front) {
		return false;
	}
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return true;
}


bool PopQueue_Sq(SqQueue& Q, QElemtype& e) {
	if (Q.front == Q.rear) {
		return false;
	}
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return true;
}

int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

