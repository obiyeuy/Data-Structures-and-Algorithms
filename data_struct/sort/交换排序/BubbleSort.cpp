// n-1次冒泡
// n-1-i

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

// void bubbleSort(int array[], int length)
// {
//     for (int i = 0; i < length - 1; i++)
//     {
//         for (int j = 0; j < length - 1 - i; j++)
//         {
//             if (array[j] > array[j + 1])
//             {
//                 int tmp = array[j + 1];
//                 array[j + 1] = array[j];
//                 array[j] = tmp;
//             }
//         }
//         printArray(array,length);
//     }
// }

void bubbleSort(int array[],int length){
    for(int i = 0;i<length-1;i++){
        for(int j = 0;j<length-1-i;j++){
            if(array[j+1]<array[j]){
                int tmp = array[j+1];
                array[j+1] = array[j];
                array[j]  =tmp;
            }
        }
        printArray(array,length);
    }
}

void bubbleSortAdvanced(int array[],int length){
    int flag = 0;
    for(int i = 0;i<length-1 && flag == 0;i++){
        flag = 1;
        for(int j = 0;j<length-1-i;j++){
            if(array[j+1]<array[j]){
                int tmp = array[j+1];
                array[j+1] = array[j];
                array[j]  =tmp;
                flag = 0;
            }
        }
        printArray(array,length);
    }
}

int main()
{
    int array[10] = {49, 38, 65, 97, 76, 13, 27, 49};
    printArray(array, 8);
    // bubbleSort(array, 8);
    bubbleSortAdvanced(array,8);
    return 0;
}
