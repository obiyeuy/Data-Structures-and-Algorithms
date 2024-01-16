#include "stdio.h"
#include "stdlib.h"
#include "stack_op.h" 
#include "math.h"//OVERFLOW�ĺ궨�������ڴ�
Status InitStack (SqStack1 &S)
{// ����һ����ջS
  S.base=(ElemType1*)malloc(STACK_INIT_SIZE*sizeof(ElemType1));
   if (!S.base) exit (OVERFLOW); //�洢����ʧ��
   S.top = S.base;
   S.stacksize = STACK_INIT_SIZE;
   return OK;
}
 Status Push (SqStack1 &S, SElemType1 e) {//��ջ
   if (S.top - S.base >= S.stacksize) {//ջ����׷�Ӵ洢�ռ�
      S.base = (ElemType1 *) realloc ( S.base,
                (S.stacksize + STACKINCREMENT) * sizeof (ElemType1));
       if (!S.base) exit (OVERFLOW); //�洢����ʧ��
       S.top = S.base + S.stacksize;
       S.stacksize += STACKINCREMENT;
   }
   *S.top++ = e;
    return OK;
}
 Status Pop (SqStack1 &S, SElemType1 &e) {//��ջ
     // ��ջ���գ���ɾ��S��ջ��Ԫ�أ�
     // ��e������ֵ��������OK��
     // ���򷵻�ERROR
    if (S.top == S.base) return ERROR;
    e = *--S.top;
    return OK;
}
 Status StackEmpty(SqStack1 S){//��ջ��
	 if(S.base == S.top) return TRUE;
	 return FALSE;
 }

 Status GetTop(SqStack1 &S, SElemType1 &e){//��ȡջ��Ԫ��1
	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
	if(S.top == S.base) return ERROR;
	e = *(S.top-1);
	return OK; 
 }

  SElemType1 GetTop(SqStack1 &S){//����ջ��Ԫ��2
	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
	if(S.top == S.base) return NULL;
	SElemType1 e = *(S.top-1);
	return e; 
 }
