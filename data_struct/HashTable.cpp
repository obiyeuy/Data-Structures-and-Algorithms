// hashtable:
// 哈希冲突：
// 开放地址法：线性探测法   二次探测法
// 链地址法: 拉链法

#include<stdio.h>
#include<stdlib.h>

#define NUM 5

typedef struct HashList{
    int num;
    char* data;
}HashList;

HashList* initList(){
    HashList* list= (HashList*)malloc(sizeof(HashList));
    list->num = 0;
    list->data = (char*)malloc(sizeof(char)*NUM);
    for(int i = 0;i<NUM;i++){
        list->data[i] = 0;
    }
    return list;
}

int hash(int data){
    return data % NUM;    
}

void put(HashList* list,char data){
    int index = hash(data);
    if(list->data[index]!=0){   //线性探测法
        int count  = 1;
        while(list->data[index] !=0){
            index = hash(hash(data)+count);
            count++;
        }
    }
    list->data[index] = data;
}

int main(){
    HashList* list = initList();
    put(list,'A');
    put(list,'F');
    printf("%c ",list->data[0]);
    printf("%c",list->data[1]);
    return 0;
}