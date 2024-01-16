#include <stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#define MAX 256

typedef struct TreeNode{
    int weight;
    int parent;
    int lchild;
    int rchild;
}TreeNode;

typedef struct HFTree{
    int length;
    TreeNode* data;
}HFTree;

typedef struct StackNode
{
    int data;
    struct StackNode *next;
} StackNode;

StackNode *initStack()
{
    StackNode *S = (StackNode *)malloc(sizeof(StackNode));
    S->data = 0;
    S->next = NULL;
    return S;
}

int isEmpty(StackNode *S)
{
    if (S->data == 0 || S->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int top(StackNode *S)
{
    if (isEmpty(S))
    {
        return -1;
    }
    else
    {
        return S->next->data;
    }
}

int pop(StackNode *S)
{
    if (isEmpty(S))
    {
        return -1;
    }
    else
    {
        StackNode *node = S->next;
        int data = node->data;
        S->next = node->next;
        S->data--;
        free(node);
        return data;
    }
}

void push(StackNode *S, int data)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->data = data;
    node->next = S->next;
    S->next = node;
    S->data++;
}

void printStack(StackNode *S)
{
    StackNode *node = S->next;
    while (node)
    {
        printf("%d", node->data);
        node = node->next;
    }
}

HFTree* initHFTree(int* weight,int length){
    HFTree* T = (HFTree*)malloc(sizeof(HFTree));
    T->data = (TreeNode*)malloc(sizeof(TreeNode)*(2*length-1));
    T->length = length;
    for(int i = 0;i<length;i++){
        T->data[i].weight = weight[i];
        T->data[i].parent = 0;
        T->data[i].lchild = -1;
        T->data[i].rchild = -1;
    }
    return T;
}

int* getMin(HFTree* T){
    int min= MAX;
    int secondMin = MAX;
    int minIndex;
    int secondIndex;
    for(int i = 0;i<T->length;i++){
        if(T->data[i].parent == 0 && min>T->data[i].weight){
            min = T->data[i].weight;
            minIndex = i;
        }
    }
    for(int i = 0;i<T->length;i++){
        if(T->data[i].parent == 0 && secondMin>T->data[i].weight && i!=minIndex){
            secondMin = T->data[i].weight;
            secondIndex = i;
        }
    }
    int* res = (int*)malloc(sizeof(int)*2);
    res[0] = minIndex;
    res[1] = secondIndex;
    return res;
}

void createTree(HFTree* T){
    int* res;
    int minIndex;
    int secondIndex;
    int length = 2*T->length-1;
    for(int i = T->length;i<length;i++){
        res = getMin(T);
        minIndex = res[0];
        secondIndex = res[1];
        T->data[i].weight = T->data[minIndex].weight+T->data[secondIndex].weight;
        T->data[i].lchild = minIndex;
        T->data[i].rchild = secondIndex;
        T->data[minIndex].parent = i;
        T->data[secondIndex].parent = i;
        T->length++;
    }
}

void findHFCode(HFTree* T,int index){
    StackNode* S = initStack();
    while(T->data[index].parent != 0){
        int parent = T->data[index].parent;
        if(T->data[parent].lchild == index){
            push(S,0);
        }else{
            push(S,1);
        }
        index = parent;
    }
    printStack(S);
    printf("\n");
}

int main()
{
    char tmp[MAX] = {0};
    cin.getline(tmp,MAX);
    char str[26];
    for(int i =0;i<26;i++){
        str[i] = 0;
    }
    for (int i = 0; i < MAX; i++)
    {
        if ('a' <= tmp[i] && tmp[i] <= 'z')
        {
            str[tmp[i]-'a']++;
        }
    }
    int count = 0;
    for(int i = 0;i<26;i++){
        if(str[i]>0){
            count++;
        }
    }
    int weight[count];
    char alphabet[count];
    int index = 0;
    for(int i = 0;i<26;i++){
        if(str[i]>0){
            weight[index] = str[i];
            alphabet[index] = (char)(i+'a');
            index++;
        }
    }
    HFTree* tree = initHFTree(weight,count);
    createTree(tree);
    for(int i = 0;i<count;i++){
        printf("%c(%d)",alphabet[i],tree->data[i].weight);
        findHFCode(tree,i);
    }
    int sum = 0;
    for(int i = count;i<tree->length;i++){
        sum += tree->data[i].weight;
    }
    printf("%d",sum);
    printf("\n");
    // for(int i = 0;i<count;i++){
    //     findHFCode(tree,i);
    // }
    return 0;
}