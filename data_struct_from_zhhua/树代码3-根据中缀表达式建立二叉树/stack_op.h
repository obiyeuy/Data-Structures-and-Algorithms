
#define OK 1
#define ERROR 0
/*符号栈 +，-，*，/,...*/
#define TRUE 1
#define FALSE 0
typedef int Status;

//----- 栈的顺序存储表示 -----
#define  STACK_INIT_SIZE  100
#define  STACKINCREMENT   10
typedef  char SElemType1, ElemType1;
typedef struct {
  SElemType1  *base;    
  SElemType1  *top;  
  int  stacksize;    
} SqStack1,Stack1;
Status InitStack (SqStack1 &S);//初始化栈
Status Push (SqStack1 &S, SElemType1 e);//入栈
Status Pop (SqStack1 &S, SElemType1 &e);//出栈
Status StackEmpty(SqStack1 S);//判是否为空栈
Status GetTop(SqStack1 &S, SElemType1 &e);//获取栈顶元素到e中
SElemType1 GetTop(SqStack1 &S);//返回栈顶元素