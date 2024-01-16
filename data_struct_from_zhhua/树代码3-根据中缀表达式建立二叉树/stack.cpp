#include "stdio.h"
#include "stdlib.h"
#include "stack.h" 
#include "math.h"//OVERFLOW�ĺ궨�������ڴ�
Status InitStack (SqStack &S)
{// ����һ����ջS
  S.base=(ElemType*)malloc(STACK_INIT_SIZE*sizeof(ElemType));
   if (!S.base) exit (OVERFLOW); //�洢����ʧ��
   S.top = S.base;
   S.stacksize = STACK_INIT_SIZE;
   return OK;
}
 Status Push (SqStack &S, SElemType e) {//��ջ
   if (S.top - S.base >= S.stacksize) {//ջ����׷�Ӵ洢�ռ�
      S.base = (ElemType *) realloc ( S.base,
                (S.stacksize + STACKINCREMENT) * sizeof (ElemType));
       if (!S.base) exit (OVERFLOW); //�洢����ʧ��
       S.top = S.base + S.stacksize;
       S.stacksize += STACKINCREMENT;
   }
   *S.top++ = e;
    return OK;
}
 Status Pop (SqStack &S, SElemType &e) {//��ջ
     // ��ջ���գ���ɾ��S��ջ��Ԫ�أ�
     // ��e������ֵ��������OK��
     // ���򷵻�ERROR
    if (S.top == S.base) return ERROR;
    e = *--S.top;
    return OK;
}
 Status StackEmpty(SqStack S){//��ջ��
	 if(S.base == S.top) return TRUE;
	 return FALSE;
 }

 Status GetTop(SqStack &S, SElemType &e){//��ȡջ��Ԫ��
	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
	if(S.top == S.base) return ERROR;
	e = *(S.top-1);
	return OK; 
 }
