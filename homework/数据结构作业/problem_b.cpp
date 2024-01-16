#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct StackNode
{
    char date;
    struct StackNode* next;
}StackNode;
typedef struct LinkStack
{
    StackNode* top;
}LinkStack;
int isPalindrome(char * s)
{
    LinkStack* start=NULL;
    StackNode* node=NULL;
    start=(LinkStack*)malloc(sizeof(LinkStack));
    int num=strlen(s);
    //将数组中数字字母字符依次入栈
    for(int i=0;i<num;i++)
    {
        //如果是数字字母字符就入栈
        if((s[i]>=65&&s[i]<=90)||(s[i]>=97&&s[i]<=122)||(s[i]>=48)&&(s[i]<=57))
        {
            node=(StackNode*)malloc(sizeof(StackNode));
            node->date=s[i];
            node->next=start->top;
            start->top=node;
        }
    }
    //再次遍历数组，将数组中字符是数字字母的元素与出栈元素比较
    StackNode* p=NULL;
    for(int i=0;i<num;i++)
    {
        //如果是数字字母字符就出栈
        if((s[i]>=65&&s[i]<=90)||(s[i]>=97&&s[i]<=122)||(s[i]>=48)&&(s[i]<=57))
        {
            if(start->top->date!=s[i])
            {
                return 0;
            }
            p=start->top;
            start->top=start->top->next;
            free(p);
        }

    }
    return 1;
}

int main(void) {
    char s[100];
    scanf("%s", s);
    printf("%d",isPalindrome(s));
    return 0;
}
