#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;           // 数据域
    struct node *next; // 指针域
} KeyNode;

void bucketSort(int array[], int size, int bucket_size)
{
    int i, j; // 数组，数组长度，桶的大小
    // 定义动态的指针数组
    KeyNode **bucket_num = (KeyNode **)malloc(bucket_size * sizeof(KeyNode *));
    for (i = 0; i < bucket_size; i++)
    {
        bucket_num[i] = (KeyNode *)malloc(sizeof(KeyNode)); // 为每个链表定义头结点
        bucket_num[i]->num = 0;
        bucket_num[i]->next = NULL; // 指针变量初始化为空
    }
    for (j = 0; j < size; j++) // 准备插入
    {
        KeyNode *node = (KeyNode *)malloc(sizeof(KeyNode)); // 定义一个节点
        node->num = array[j];                               // 数据域存数据
        node->next = NULL;                                  // 指向空
        int index = array[j] / 100; // 映射函数 计算桶号
        KeyNode *p = bucket_num[index]; // p指向链表的头
        // 链表结构的插入排序
        while (p->next != NULL && p->next->num <= node->num)
        {
            p = p->next; // 1.链表为空，p->next==NULL，进入不了循环
        }                // 2.链表不为空，因为链表从无开始按顺序插入，数据为有序的，
                         // 可以找到    前一个节点 <= node <=后一个节点
        // 节点插入链表
        node->next = p->next;
        p->next = node;
        (bucket_num[index]->num)++; // 记录一下该链表中有几个有效节点
    }
    // 打印结果
    KeyNode *k = NULL; // 定义一个空的结构体指针用于储存输出结果
    for (i = 0; i < bucket_size; i++)
    {
        // for(k = bucket_num[i]->next;k!=NULL;k=k->next)//通过最后一个指针指向空
        k = bucket_num[i]->next;
        for (int m = 0; m < bucket_num[i]->num; m++) // 通过头指针记录节点数
        {
            printf("%d ", k->num);
            k = k->next;
        }
        printf("\n");
    }
}

int main()
{
    int array[20] = {491, 381, 615, 917, 716, 13, 217, 419, 19, 138, 61, 419, 419, 38, 615, 917, 16, 113, 217, 419};
    bucketSort(array, 20, 3); // 数组名，数组长度，桶的个数
}