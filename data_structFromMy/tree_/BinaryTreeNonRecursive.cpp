#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

typedef struct StackNode
{
    TreeNode *data;
    struct StackNode *next;
} StackNode;

void createTree(TreeNode **T, char *data, int *index)
{
    char ch;
    ch = data[*index];
    *index += 1;
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

StackNode *initStack()
{
    StackNode *S = (StackNode *)malloc(sizeof(StackNode));
    S->data = NULL;
    S->next = NULL;
    return S;
}

void push(TreeNode *data, StackNode *S)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->data = data;
    node->next = S->next;
    S->next = node;
}

int isEmpty(StackNode *S)
{
    if (S->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

StackNode *pop(StackNode *S)
{
    if (isEmpty(S))
    {
        return NULL;
    }
    else
    {
        StackNode *node = S->next;
        S->next = node->next;
        return node;
    }
}

void printStack(StackNode *S)
{
    StackNode *node = S->next;
    while (node)
    {
        printf("%c ", node->data->data);
        node = node->next;
    }
}

void preOrder(TreeNode *T)
{
    TreeNode *node = T;
    StackNode *S = initStack();
    while(node||!isEmpty(S)){
        if(node){
            printf("%c ",node->data);
            push(node,S);
            node = node->lchild;
        }else{
            node = pop(S)->data;
            node = node->rchild;
        }
    }

}

void inOrder(TreeNode *T)
{
    TreeNode *node = T;
    StackNode *S = initStack();
    while(node||!isEmpty(S)){
        if(node){
            push(node,S);
            node = node->lchild;
        }else{
            node = pop(S)->data;
            printf("%c ",node->data);
            node= node->rchild;
        }
    }
}

void postOrder(TreeNode *T)
{
    TreeNode *node = T;
    StackNode *S = initStack();
    StackNode* tmp = initStack();
    while(node||!isEmpty(S)){
        if(node){
            push(node,tmp);
            push(node,S);
            node = node->rchild;
        }else{
            node = pop(S)->data;
            node= node->lchild;
        }
    }
    printStack(tmp);
}

int main()
{
    TreeNode *T;
    // char data[] = "AB##C##";
    char data[] = "ABD##E##CF##G##";
    int index = 0;
    createTree(&T, data, &index);
    preOrder(T);
    printf("\n");
    inOrder(T);
    printf("\n");
    postOrder(T);
    return 0;
}