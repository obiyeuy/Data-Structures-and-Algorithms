//二分查找
// 要求线性表必须有序

// ASL:[(n+1)*log2(n+1)-1]/2   近似于log2(n+1)-1   近似于log2(n)
// 时间复杂度O(logn)
// 空间复杂度O(1)


#include<stdio.h>
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

int binarySearch(int key,List *list)
{
    int start = 0;
    int end = list->num-1;
    int mid;
    while(start<=end){
        mid = (start+end)/2;
        if(list->data[mid]<key){
            start = mid+1;
        }else if(list->data[mid]>key){
            end = mid-1;
        }else{
            return mid;
        }
    }
    return -1;
}

int binarySearchRecursion(int key,List* list,int start,int end){
    if(start >= end){
        if(list->data[start] == key){
            return start;
        }else{
            return -1;
        }
    }
    int mid = (start+end)/2;
    if(list->data[mid]<key){
        return binarySearchRecursion(key,list,mid+1,end);
    }else if(list->data[mid]>key){
        return binarySearchRecursion(key,list,start,mid-1);
    }else{
        return mid;
    }
}

int main()
{
    List *list = initList(9);
    listAdd(list, 1);
    listAdd(list, 2);
    listAdd(list, 3);
    listAdd(list, 4);
    listAdd(list, 5);
    listAdd(list, 6);
    listAdd(list, 7);
    listAdd(list, 8);
    listAdd(list, 9);
    printList(list);
    printf("data %d in %d\n", 7, binarySearch(7, list));
    printf("data %d in %d\n", 10, binarySearch(10, list));
    printf("data %d in %d\n", 1, binarySearch(1, list));
    printf("data %d in %d\n", 3, binarySearch(3, list));
    printf("\n");
    printf("data %d in %d\n", 7, binarySearchRecursion(7, list, 0, list -> num - 1));
    printf("data %d in %d\n", 10, binarySearchRecursion(10, list, 0, list -> num - 1));
    printf("data %d in %d\n", 1, binarySearchRecursion(1, list, 0, list -> num - 1));
    printf("data %d in %d\n", 3, binarySearchRecursion(3, list, 0, list -> num - 1));
    return 0;
}
