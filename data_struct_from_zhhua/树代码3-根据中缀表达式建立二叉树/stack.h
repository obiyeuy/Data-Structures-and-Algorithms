#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
//----- ջ��˳��洢��ʾ -----
#define  STACK_INIT_SIZE  100
#define  STACKINCREMENT   10
typedef char TElemType;
typedef struct BiTNode { // ���ṹ
    TElemType      data;
    struct BiTNode  *lchild, *rchild; // ���Һ���ָ��                                  
} BiTNode, *BiTree;
typedef  BiTree SElemType, ElemType;
typedef struct {
  SElemType  *base;    
  SElemType  *top;  
  int  stacksize;    
} SqStack,Stack;
Status InitStack (SqStack &S);//��ʼ��ջ
Status Push (SqStack &S, SElemType e);//��ջ
Status Pop (SqStack &S, SElemType &e);//��ջ
Status StackEmpty(SqStack S);//���Ƿ�Ϊ��ջ
Status GetTop(SqStack &S, SElemType &e);//��ȡջ��Ԫ��