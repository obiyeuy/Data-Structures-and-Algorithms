#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
} Stack;

Stack *create_stack()
{ // 创建空栈
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, int data)
{ // 入栈操作
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
}

int pop(Stack *stack)
{ // 出栈操作
    if (stack->top == NULL)
    {
        return -1; // 如果栈为空，则返回-1
    }
    Node *node = stack->top;
    int data = node->data;
    stack->top = node->next;
    free(node);
    return data;
}

int top(Stack *stack)
{ // 返回栈顶元素
    if (stack->top == NULL)
    {
        return -1; // 如果栈为空，则返回-1
    }
    return stack->top->data;
}

int is_operator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int priority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

int calculate(int a, char op, int b)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        exit(1);
    }
}

/**
 * 计算表达式结果的函数。
 *
 * param expression 表达式字符串
 * return 表达式的计算结果
 */
int evaluate_expression(char *expression)
{
    Stack *s1 = create_stack(); // 操作数栈，用于存储操作数
    Stack *s2 = create_stack(); // 操作符栈，用于存储操作符

    for (int i = 0; expression[i] != '\0'; i++)
    {
        if (is_operator(expression[i]))
        { // 如果当前字符为操作符
            while (s2->top != NULL && priority(top(s2)) >= priority(expression[i]))
            {
                // 如果操作符栈不为空，并且栈顶操作符的优先级大于等于当前操作符的优先级
                int b = pop(s1);                  // 出栈一个操作数作为运算的右操作数
                int a = pop(s1);                  // 再出栈一个操作数作为运算的左操作数
                char op = pop(s2);                // 出栈一个操作符
                int result = calculate(a, op, b); // 计算两个操作数和操作符的结果
                push(s1, result);                 // 将计算结果入栈到操作数栈中
            }
            push(s2, expression[i]); // 当前操作符入栈到操作符栈中
        }
        else if (expression[i] == '(')
        {                            // 如果当前字符为左括号
            push(s2, expression[i]); // 入栈到操作符栈中
        }
        else if (expression[i] == ')')
        { // 如果当前字符为右括号
            while (top(s2) != '(')
            {                                     // 循环执行直到遇到左括号
                int b = pop(s1);                  // 出栈一个操作数作为运算的右操作数
                int a = pop(s1);                  // 再出栈一个操作数作为运算的左操作数
                char op = pop(s2);                // 出栈一个操作符
                int result = calculate(a, op, b); // 计算两个操作数和操作符的结果
                push(s1, result);                 // 将计算结果入栈到操作数栈中
            }
            pop(s2); // 弹出左括号
        }
        else
        {                                  // 如果当前字符为数字
            int num = expression[i] - '0'; // 将当前字符转换成数字
            while (expression[i + 1] >= '0' && expression[i + 1] <= '9')
            {
                // 如果下一个字符也是数字，则将其合并到一起
                num = num * 10 + expression[++i] - '0';
            }
            push(s1, num); // 将数字入栈到操作数栈中
        }
    }

    // 处理剩余的操作符
    while (s2->top != NULL)
    {
        int b = pop(s1);                  // 出栈一个操作数作为运算的右操作数
        int a = pop(s1);                  // 再出栈一个操作数作为运算的左操作数
        char op = pop(s2);                // 出栈一个操作符
        int result = calculate(a, op, b); // 计算两个操作数和操作符的结果
        push(s1, result);                 // 将计算结果入栈到操作数栈中
    }

    return pop(s1); // 返回最终的计算结果
}

int main()
{
    char expression[50];
    scanf("%s", expression);
    int result = evaluate_expression(expression);
    printf("%d\n", result);
    return 0;
}