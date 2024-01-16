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

//字符串赋值
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

void printString(String *S)
{
    for (int i = 0; i < S->len; i++)
    {
        printf("%c ", S->data[i]);
    }
}

void forceMatch(String *master, String *sub)
{
    int i = 0;
    int j = 0;
    while (i < master->len && j < sub->len)
    {
        if (master->data[i] == sub->data[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == sub->len)
    {
        printf("force match success.\n");
    }
    else
    {
        printf("force match fail.\n");
    }
}

int main()
{
    String *S = initString();
    String* S1 = initString();
    String* S2 = initString();

    //报警告 ISO C++ forbids converting a string constant to 'char*'
    //但仍可运行，C语言文件也可以
    StringAssign(S, "abcdefg");
    StringAssign(S1,"cde");
    StringAssign(S2,"fgh");
    printString(S);
    printf("\n");
    forceMatch(S,S1);
    forceMatch(S,S2);
    return 0;
}

// int main(/*int argc,*/ char *argv[])
// {
//     // argc是argv的长度，argv[0]是文件名,argv[1]、argv[2]...是传的参数
//     // 手动编译可行，直接运行就相当于没有传参
//     String *S = initString();
//     String *S1 = initString();

//     StringAssign(S, argv[1]);
//     StringAssign(S1, argv[2]);
//     printString(S);
//     printf("\n");
//     forceMatch(S, S1);
//     return 0;
// }