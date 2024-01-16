// 希尔排序：又称缩小增量排序   减少记录个数  序列基本有序
// 步骤：
// 1.从以k为步长开始，对组内的数字进行插入排序
// 2.缩小步长k，重复第一步，知道k=1

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

// void shellSort(int array[], int length, int step)
// {
//     for (int i = 0; i < length; i++)
//     {
//         for (int j = i + step; j < length; j += step)
//         {
//             for (int k = i; k < j; k += step)
//             {
//                 if (array[j] < array[k])
//                 {
//                     int tmp = array[j];
//                     for (int l = j - step; l >= k; l -= step)
//                     {
//                         array[l + step] = array[l];
//                     }
//                     array[k] = tmp;
//                 }
//             }
//         }
//     }
// }

void shellSort(int array[],int length,int step){
    int j,tmp;
    for(int i = step;i<length;i++){
        if(array[i]<array[i-step]){
            tmp = array[i];
            for(j = i-step;j>=0 && (array[j]>tmp) ;j -=step){
                array[j+step] = array[j];
            }
            array[j+step] = tmp;
        }
    }
}

int main()
{
    int array[10] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
    int step[3] = {5, 3, 1};
    printArray(array, 10);
    for (int i = 0; i < 3; i++)
    {
        shellSort(array, 10, step[i]);
        printArray(array, 10);
    }
    return 0;
}

