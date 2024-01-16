//带哨兵的顺序查找
// ASL:平均查找长度     
// 平均查找长度:[(n+1)*n/2]*(1/n)      算法复杂度O(n)
// 顺序查找

#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int *data;
    int length; // 总长度
    int num;    // 当前已存储长度
} List;

List *initList(int length)
{
    List *list = (List *)malloc(sizeof(List));
    list->length = length;
    list->data = (int *)malloc(sizeof(int) * length);
    list->num = 1;  //第一个存哨兵
    list->data[0] = -1; //哨兵赋值为-1
    return list;
}

void listAdd(List *list, int data)
{
    list->data[list->num] = data;
    list->num += 1;
}

void printList(List *list)
{
    for (int i = 0; i < list->num; i++)
    {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int sequenceSearch(List *list, int key)
{
    int i;
    list->data[0] = key; //将查找值赋值给哨兵
    for (i = (list->num)-1;list->data[i]!=key; i--);
    return i;   //没找到会返回0
}

int main()
{
    List *list = initList(5);
    listAdd(list, 4);
    listAdd(list, 5);
    listAdd(list, 6);
    listAdd(list, 7);
    printList(list);
    printf("%d\n", sequenceSearch(list, 4));
    printf("%d\n", sequenceSearch(list, 1));
    return 0;
}