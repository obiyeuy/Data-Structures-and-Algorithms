#include <stdlib.h>
#include <stdio.h>

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
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

void inThreadTree(TreeNode *T, TreeNode **pre)
{
    if (T)
    {
        inThreadTree(T->lchild, pre);
        // do something
        if (T->lchild == NULL)
        { // 建前驱线索
            T->ltag = 1;
            T->lchild = *pre;
        }
        if (*pre != NULL && (*pre)->rchild == NULL)
        // if ((*pre)->rchild == NULL)   错误
        { // 建后继线索
            (*pre)->rtag = 1;
            (*pre)->rchild = T;
        }
        *pre = T;
        inThreadTree(T->rchild, pre);
    }
}

// 找到最左边的节点  ????还要继续看!!!!
TreeNode *getFirst(TreeNode *T)
{
    while (T->ltag == 0)
    {
        T = T->lchild;
    }
    return T;
}
TreeNode *getNext(TreeNode *node)
{
    if (node->rtag == 1)
    {
        return node->rchild;
    }
    else
    {
        return getFirst(node->rchild);
    }
}

int main()
{
    TreeNode *T;
    TreeNode *pre = NULL;
    // char data[] = "AB##C##";
    char data[] = "ABD##E##CF##G##";
    int index = 0;
    createTree(&T, data, &index);
    inThreadTree(T, &pre);
    // pre->rtag = 1;   ????
    // pre->rchild = NULL;
    //中序遍历
    for (TreeNode *node = getFirst(T); node != NULL; node = getNext(node))
    {
        printf("%c ", node->data);
    }
    return 0;
}