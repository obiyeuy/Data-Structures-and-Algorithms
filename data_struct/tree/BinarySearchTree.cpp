// 二分查找树就是一颗二阶的多路平衡查找树

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

typedef struct StackNode
{
    TreeNode *data;
    struct StackNode *next;
} StackNode;

TreeNode *bstSearch(TreeNode *T, int key)
{
    if (T)
    {
        if (T->data == key)
        {
            return T;
        }
        else if (key < T->data)
        {
            return bstSearch(T->lchild, key);
        }
        else
        {
            return bstSearch(T->rchild, key);
        }
    }
    else
    {
        return NULL;
    }
}

void bstInsert(TreeNode **T, int data)
{
    if (*T == NULL)
    {
        *T = (TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data = data;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
    }
    else if (data == (*T)->data)
    {
        return;
    }
    else if (data < (*T)->data)
    {
        bstInsert(&((*T)->lchild), data);
    }else{
        bstInsert(&((*T)->rchild), data);
    }
}

StackNode* initStack(){
    StackNode* S = (StackNode*)malloc(sizeof(StackNode));
    S->data = NULL;
    S->next = NULL;
    return S;
}
int isEmpty(StackNode* S){
    if(S->next == NULL){
        return 1;
    }else{
        return 0;
    }
}

void push(TreeNode* node,StackNode* S){
    StackNode* tmp = (StackNode*)malloc(sizeof(StackNode));
    tmp->data = node;
    tmp->next = S->next;
    S->next = tmp;
}

StackNode* pop(StackNode* S){
    if(isEmpty(S)){
        return NULL;
    }else{
        StackNode* tmp = S->next;
        S->next = tmp->next;
        return tmp;
    }
}

//非递归中序遍历
void inOrder(TreeNode *T)
{
    StackNode* S = initStack();
    TreeNode* node = T;
    while(node || !isEmpty(S)){
        if(node){
            push(node,S);
            node = node->lchild;
        }
        else{
            node = pop(S)->data;
            printf("%d ",node->data);
            node = node->rchild;
        }
    }
}

// 求结点在二叉排序树中层次的算法   层次是从上向下找的
int lev=  0;
void level(TreeNode* T,int x){
    if(T!=NULL){
        lev++;
        if(T->data == x){
            return;
        }else if(T->data>x){
            level(T->lchild,x);
        }else{
            level(T->rchild,x);
        }
    }
}

int main()
{
    TreeNode *T = NULL;
    int nums[] = {4,5,19,23,1,8};
    for(int i = 0;i<6;i++){
        bstInsert(&T,nums[i]);
    }
    inOrder(T);
    level(T,19);
    printf("\n%d",lev);
    return 0;
}