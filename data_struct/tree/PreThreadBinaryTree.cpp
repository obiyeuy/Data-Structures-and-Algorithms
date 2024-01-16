#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int ltag;
    int rtag;
} TreeNode;

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
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

void PreThreadBinaryTree(TreeNode *T, TreeNode **pre)
{
    if (T)
    {
        if (T->lchild == NULL)
        {
            T->ltag = 1;
            T->lchild = *pre;
        }
        if (*pre != NULL && (*pre)->rchild == NULL)
        {
            (*pre)->rtag = 1;
            (*pre)->rchild = T;
        }
        *pre = T;
        if (T->ltag == 0)
        {
            PreThreadBinaryTree(T->lchild, pre);
        }
        PreThreadBinaryTree(T->rchild, pre);
    }
}

// 遍历
// TreeNode *getNext(TreeNode *node)
// {
//     if (node->rtag == 1)
//     {
//         return node->rchild;
//     }
//     else
//     {
//         if (node->ltag == 0)
//         {
//             return node->lchild;
//         }
//         else
//         {
//             return node->rchild;
//         }
//     }
// }

TreeNode *getNext(TreeNode *node)
{
    if (node->rtag == 1 || node->ltag == 1)
    {
        return node->rchild;
    }
    else
    {
        return node->lchild;
    }
}

int main()
{
    TreeNode *T;
    TreeNode *pre = NULL;
    // char data[] = "AB##C##";
    char data[] = "ABD##E##CF##G##";
    int index = 0;
    createTree(&T,data,&index);
    PreThreadBinaryTree(T, &pre);
    // pre->rtag = 1;   ????
    // pre->rchild = NULL;
    for (TreeNode *node = T; node != NULL; node = getNext(node))
    {
        printf("%c ", node->data);
    }
    return 0;
}