
#define OK 1
#define ERROR 0
/*����ջ +��-��*��/,...*/
#define TRUE 1
#define FALSE 0
typedef int Status;

//----- ջ��˳��洢��ʾ -----
#define  STACK_INIT_SIZE  100
#define  STACKINCREMENT   10
typedef  char SElemType1, ElemType1;
typedef struct {
  SElemType1  *base;    
  SElemType1  *top;  
  int  stacksize;    
} SqStack1,Stack1;
Status InitStack (SqStack1 &S);//��ʼ��ջ
Status Push (SqStack1 &S, SElemType1 e);//��ջ
Status Pop (SqStack1 &S, SElemType1 &e);//��ջ
Status StackEmpty(SqStack1 S);//���Ƿ�Ϊ��ջ
Status GetTop(SqStack1 &S, SElemType1 &e);//��ȡջ��Ԫ�ص�e��
SElemType1 GetTop(SqStack1 &S);//����ջ��Ԫ��