// 排序指标：
// 排序的稳定性：对于序列中相同元素，其相同元素相对顺序不变就是稳定算法
// 内部排序：在内存中完成
// 外部排序：内存放不下，一次取一部分排序

// 插入排序：稳定算法   比较简单
// 步骤：
// 1.从第二个元素开始，去跟他之前的序列比较，找到合适的元素插入
// 2.移动元素，指针后移

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

void insertSort(int array[], int length)
{
    // 外层循环从第二个元素开始比较，比较第零个元素到他前一个元素有没有合适的位置插入
    for (int i = 1; i < length; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (array[i] < array[j])
            {
                int tmp = array[i];
                for (int k = i - 1; k >= j; k--)
                {
                    array[k + 1] = array[k];
                }
                array[j] = tmp;
            }
        }
        printArray(array, length);
    }
}

void BinaryInsertSort(int array[], int length)
{
    int i, j, tmp;
    for (i = 1; i < length; i++)
    {
        // if (array[i] < array[i - 1])
        // {
            tmp = array[i];
            int left = 0;
            int right = i - 1;
            int mid;
            while (left <= right)
            {
                mid = (left + right) / 2;
                if (tmp < array[mid])
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
            for (j = i - 1; j >= right + 1; j--)
            {
                array[j + 1] = array[j];
            }
            array[right + 1] = tmp;
        // }
        printArray(array, length);
    }
}

int main()
{
    int array[6] = {4, 3, 5, 1, 9, 6};
    printArray(array, 6);
    // insertSort(array,6);
    BinaryInsertSort(array, 6);
    return 0;
}
