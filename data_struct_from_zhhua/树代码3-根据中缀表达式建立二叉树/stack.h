#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
//----- 栈的顺序存储表示 -----
#define  STACK_INIT_SIZE  100
#define  STACKINCREMENT   10
typedef char TElemType;
typedef struct BiTNode { // 结点结构
    TElemType      data;
    struct BiTNode  *lchild, *rchild; // 左右孩子指针                                  
} BiTNode, *BiTree;
typedef  BiTree SElemType, ElemType;
typedef struct {
  SElemType  *base;    
  SElemType  *top;  
  int  stacksize;    
} SqStack,Stack;
Status InitStack (SqStack &S);//初始化栈
Status Push (SqStack &S, SElemType e);//入栈
Status Pop (SqStack &S, SElemType &e);//出栈
Status StackEmpty(SqStack S);//判是否为空栈
Status GetTop(SqStack &S, SElemType &e);//获取栈顶元素