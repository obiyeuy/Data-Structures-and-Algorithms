// 一次交换消除多个逆序
// 从中选择一个枢纽，比枢纽小的放在枢纽左边，比枢纽大的放在枢纽右边
// 然后在左边和右边分别选一个枢纽，对左边和右边分别进行快速排序

// 需要两个指针

// 不稳定的排序算法
// 适合已知长度的顺序表，不适合链表
// 序列较长的话比较好

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void merge(int array[], int low, int mid, int high)
{
    int arrayTmp[MAX];
    for (int i = low; i < high + 1; i++)
    {
        arrayTmp[i] = array[i];
    }
    int i = low, j = mid + 1, k = low;
    // 只有在这种情况下 才不会越界
    while (i < mid + 1 && j < high + 1)
    {
        // A的元素暂存在B里，因为不能再A上原地操作，会打乱数据
        // 这也是为什么二路归并排序(合并排序)空间复杂度是O(n)的原因
        // 我们这里把值小的放在前面，最后排序结果就是从小到大
        if (arrayTmp[i] > arrayTmp[j])
        {
            array[k++] = arrayTmp[j++];
        }
        else
        {
            array[k++] = arrayTmp[i++];
        }
    }
    // 循环结束后，会有一个没有遍历结束的数组段。处理上文的情况2
    while (i < mid + 1)
        array[k++] = arrayTmp[i++];
    while (j < high + 1)
        array[k++] = arrayTmp[j++];
}

void mergeSort(int array[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(array, low, mid);
        mergeSort(array, mid + 1, high);
        merge(array, low, mid, high);
        printArray(array,10);
    }
}

int main()
{
    int array[10] = {40,55,49,73,12,27,98,81,64,36};
    printArray(array, 10);
    mergeSort(array, 0, 10);
    return 0;
}
