#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMNET 20

typedef int Elemtype;

typedef struct {
	Elemtype* elem;
	int length;
	int listsize;
}SqList;

//构造一个空的顺序表L
bool InitList(SqList* L) {
	L->elem = (Elemtype*)malloc(LIST_INIT_SIZE* sizeof(Elemtype));
	if (!L->elem) {
		return false;
	}
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return true;
}

bool IsFull(SqList L) {
	if (L.length == L.listsize) {
		return true;
	}
	return false;
}

bool IsEmpty(SqList L) {
	return L.length == 0;
}

void Inc(SqList* L) {   //扩容
	Elemtype* p = (Elemtype*)realloc(L->elem, (L->listsize + LISTINCREMNET) * sizeof(Elemtype));
	if (p != NULL) {
		L->elem = p;
	}
	L->listsize += LISTINCREMNET;
}

void ClearList(SqList* L) {
	L->length = 0;
}

void DestroyList(SqList* L) {
	free(L->elem);
	L->elem = NULL;
	L->length = 0;
	L->listsize = 0;
}

//顺序表的插入
/*
插入操作
初始条件：顺序表L已存在
操作结果：在L中的第i个位置之前插入新的数据元素e，L的长度加1
*/
bool ListInsert(SqList* L, int i, Elemtype e) {
	if (i<1 || i>L->length + 1 || IsFull(*L)) {   //当i不在范围内时
		return false;
	}
	if (i <= L->length) {    //若插入位置不在表尾
		for (int k = L->length - 1; k >= i - 1; k--) {
			L->elem[k + 1] = L->elem[k];
		}
	}
	L->elem[i - 1] = e;   //将新元素插入
	L->length++;     //长度加1
	return true;
}

//顺序表的删除
/*
删除操作
初始条件：顺序表L已存在
操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1
*/
bool ListDelete(SqList* L, int i, Elemtype* e) {
	if (i<1 || i>L->length || IsEmpty(*L)) {  //i值不合法
		return false;
	}
	if (e != NULL) {
		*e = L->elem[i - 1];
	}
	
	for (int k = i; k < L->length; k++) {
		L->elem[k - 1] = L->elem[k];
	}
	
	L->length--;  //长度减1
	return true;
}

//获取顺序表某一位置上的元素
/*
获取元素操作
初始条件：顺序表L已存在
操作结果：用e返回L中第i个数据元素的值
*/
bool GetElem_Sq(SqList L, int i, Elemtype* e) {
	if (IsEmpty(L) || i<0 || i>L.length) {
		return false;
	}
	*e = L.elem[i - 1];
	return true;
}

/*
初始条件：线性表已存在
操作结果：返回L中第一个与e满足相等关系(或其他关系)的元素位序，若这样的数据元素不存在，则返回值为-1
*/
int LocateElem(SqList L, Elemtype e) {
	if (IsEmpty(L)) {
		return -1;
	}
	for (int i = 0; i < L.length; i++) {
		if (L.elem[i] == e) {
			return i;
		}
	}
	return -1;
}

/*
初始条件：线性表L已存在
操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
*/
bool PriorElem(SqList L, Elemtype cur_e, Elemtype* pre_e) {
	if (IsEmpty(L) || LocateElem(L,cur_e) == 0) {
		return false;
	}
	*pre_e = L.elem[LocateElem(L, cur_e) - 1];
	return true;
}

/*
初始条件：线性表L已存在
操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后驱，否则操作失败，next_e无定义
*/
bool NextElem(SqList L, Elemtype cur_e, Elemtype* next_e) {
	if (IsEmpty(L) || LocateElem(L, cur_e) == L.length-1) {
		return false;
	}
	*next_e = L.elem[LocateElem(L, cur_e) + 1];
	return true;
}

//读取顺序表所有元素
bool ListTraverse(SqList L) {
	if (IsEmpty(L)) {
		return false;
	}
	for (int i = 0; i < L.length; i++) {
		printf("%d ", L.elem[i]);
	}
	printf("\n");
	return true;
}


//测试
int main(void) {
	SqList L;
	InitList(&L);
	printf("%d\n", IsEmpty(L));
	for (int i = 0; i < 70; i++) {
		ListInsert(&L, i, i);
	}
	ListTraverse(L);
	ListDelete(&L, 10, NULL);
	ListTraverse(L);
	Elemtype m = 0;
	GetElem_Sq(L, 13, &m);
	printf("%d\n",m);
	Elemtype n = 0;
	PriorElem(L, m, &n);
	printf("%d\n", n);
	NextElem(L, m, &n);
	printf("%d\n", n);
	ClearList(&L);
	ListTraverse(L);
	DestroyList(&L);
	ListInsert(&L,0,1);
}