#include <stdlib.h>
#include <stdio.h>

typedef struct String
{
    char *data;
    int len;
} String;

String *initString()
{
    String *S = (String *)malloc(sizeof(String));
    S->data = NULL;
    S->len = 0;
    return S;
}

// 字符串赋值
void StringAssign(String *S, char *data)
{
    if (S->data)
    {
        free(S->data);
    }
    int len = 0;
    char *temp = data;
    while (*temp)
    {
        len++;
        temp++;
    }
    if (len == 0)
    {
        S->data = NULL;
        S->len = 0;
    }
    else
    {
        temp = data;
        S->len = len;
        S->data = (char *)malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; i++, temp++)
        {
            S->data[i] = *temp;
        }
    }
}

// 求子串的next数组
// next数组：是当该字符与主串发生不匹配之后，next值对应索引的字符要移动到跟主串不匹配的字符对齐
// 公共前后缀：next值等于公共前后缀加1
// 后一个next值可以根据前一个next值推出
// kmp算法可以达到O(n+m)
int *getNext(String *S)
{
    int *next = (int *)malloc(sizeof(int) * S->len);
    int i = 0;
    int j = -1;
    next[i] = j;
    while (i < S->len - 1) // 此处减了1
    {
        if (j == -1 || S->data[i] == S->data[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    return next;
}

void printNext(int *next, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", next[i]);
    }
}

void kmpMatch(String *master, String *sub, int *next)
{
    int i = 0;
    int j = 0;
    while (i < master->len && j < sub->len)
    {
        if (j == -1 || master->data[i] == sub->data[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == sub->len)
    {
        printf("kmp match sccess.\n");
    }
    else
    {
        printf("kmp match fail.\n");
    }
}

void printString(String *S)
{
    for (int i = 0; i < S->len; i++)
    {
        printf("%c ", S->data[i]);
    }
}

int main()
{
    String *S = initString();
    String *S1 = initString();
    String *S2 = initString();

    // 报警告 ISO C++ forbids converting a string constant to 'char*'
    // 但仍可运行，C语言文件也可以
    StringAssign(S, "abcdefg");
    printString(S);
    printf("\n");
    StringAssign(S1, "abaccababd");
    StringAssign(S2, "def");
    int *next1 = getNext(S1);
    int *next2 = getNext(S2);
    printNext(next2, S2->len);
    printf("\n");
    kmpMatch(S, S1, next1);
    kmpMatch(S, S2, next2);
    return 0;
}