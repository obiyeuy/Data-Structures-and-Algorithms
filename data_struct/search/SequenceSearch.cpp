// ASL:平均查找长度
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
    list->num = 0;
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
    for (int i = 0; i < list->num; i++)
    {
        if (list->data[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    List *list = initList(5);
    listAdd(list, 1);
    listAdd(list, 2);
    listAdd(list, 3);
    listAdd(list, 4);
    printList(list);
    printf("%d\n", sequenceSearch(list, 4));
    printf("%d\n", sequenceSearch(list, 5));
    return 0;
}