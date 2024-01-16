// 一次交换消除多个逆序
// 从中选择一个枢纽，比枢纽小的放在枢纽左边，比枢纽大的放在枢纽右边
// 然后在左边和右边分别选一个枢纽，对左边和右边分别进行快速排序

// 需要两个指针

// 不稳定的排序算法
// 适合已知长度的顺序表，不适合链表
// 序列较长的话比较好

#include <stdio.h>
#include <stdlib.h>

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void heapAdjust(int array[], int start, int end)
{
    int tmp = array[start];
    for (int i = 2 * start + 1; i <= end; i = 2 * i + 1)
    {
        if (i < end && array[i] < array[i + 1])
        {
            ++i;
        }
        if (tmp < array[i])
        {
            array[start] = array[i];
            start = i;
        }
        else
        {
            break;
        }
    }
    array[start] = tmp;
}

void heapSort(int array[], int length)
{
    for (int i = (length - 1 - 1) / 2; i >= 0; i--)
    {
        heapAdjust(array, i, length - 1);
    }
    int tmp;
    for(int i = 0;i<length-1;i++){
        tmp = array[0];
        array[0] = array[length-1-i];
        array[length-1-i] = tmp;
        heapAdjust(array,0,length-1-i-1);
        printArray(array, 8);
    }
}

int main()
{
    int array[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    printArray(array, 8);
    heapSort(array, 8);
    return 0;
}
