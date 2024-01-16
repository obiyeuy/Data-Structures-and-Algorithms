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

void simpleSelectSort(int array[],int length){
    for(int i = 0;i<length-1;i++){
        int k = i;
        for(int j = i;j<length;j++){
            if(array[j]<array[k]){
                k = j;
            }
        }
        if(k!=i){
            int tmp = array[i];
            array[i] = array[k];
            array[k] = tmp;
        }
        printArray(array, length);
    }
}

int main()
{
    int array[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    printArray(array, 8);
    simpleSelectSort(array,8);
    return 0;
}
