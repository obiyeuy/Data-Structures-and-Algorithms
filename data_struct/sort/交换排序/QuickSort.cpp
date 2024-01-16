// 一次交换消除多个逆序
// 从中选择一个枢纽，比枢纽小的放在枢纽左边，比枢纽大的放在枢纽右边
// 然后在左边和右边分别选一个枢纽，对左边和右边分别进行快速排序

// 需要两个指针

//不稳定的排序算法
//适合已知长度的顺序表，不适合链表     
//序列较长的话比较好

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

int partition(int array[], int left, int right)
{
    int x = array[left];
    while (left < right)
    {
        while (left < right && array[right] >= x)
        {
            right--;
        }
        // if (left < right)
        // {
        //     array[left] = array[right];
        //     left++;
        // }
        array[left] = array[right];
        while (left < right && array[left] <= x)
        {
            left++;
        }
        // if (left < right)
        // {
        //     array[right] = array[left];
        //     right--;
        // }
        array[right]=array[left];
    }
    array[left] = x;
    return left;
}

void quickSort(int array[], int left, int right)
{
    if (left < right)
    {
        int index = partition(array, left, right);
        printArray(array, 8);
        quickSort(array, left, index - 1);
        quickSort(array, index + 1, right);
    }
}


int main()
{
    int array[10] = {49, 38, 65, 97, 76, 13, 27, 49};
    printArray(array, 8);
    quickSort(array, 0, 7);
    return 0;
}



// int partition(int array[],int left,int right){
//     int tmp = array[left];
//     while(left<right){
//         while(left<right && tmp>=array[right]){
//             right--;
//         }
//         if(left<right){
//             array[left] = array[right];
//             left++;
//         }
//         while(left<right && tmp<array[left]){
//             left++;
//         }
//         if(left<right){
//             array[right] = array[left];
//             right--;
//         }
//     }
//     array[left] = tmp;
//     return left;
// }

// void quickSort(int array[],int left,int right){
//     if(left<right){
//         int index = partition(array,left,right);
//         quickSort(array,left,index-1);
//         quickSort(array,index+1,right);
//     }
// }
